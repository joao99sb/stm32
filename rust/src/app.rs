use core::cell::RefCell;
use core::ops::DerefMut;
use core::sync::atomic::AtomicU32;

use hal::pac;
use hal::pac::{interrupt, Interrupt};
use hal::prelude::*;
use stm32f4xx_hal as hal;
use stm32f4xx_hal::gpio::{gpioc, PinState};

use cortex_m::interrupt::Mutex;
use hal::pac::TIM2;
use hal::timer::{CounterUs, Event};
use rtt_target::{rprintln, rtt_init_print};

use usbd_human_interface_device::device::keyboard::NKROBootKeyboardConfig;
use usbd_human_interface_device::page::Keyboard;
use usbd_human_interface_device::prelude::*;

use stm32f4xx_hal::otg_fs::{UsbBus, USB};
use usb_device::prelude::*;

static mut EP_MEMORY: [u32; 1024] = [0; 1024];

static GLOBAL_TIMER: Mutex<RefCell<Option<CounterUs<TIM2>>>> = Mutex::new(RefCell::new(None));
static GLOBAL_MILLISECONDS: AtomicU32 = AtomicU32::new(0);

fn now_ms() -> u32 {
    GLOBAL_MILLISECONDS.load(core::sync::atomic::Ordering::Acquire)
}

struct Throttler {
    last_tick: u32,
    last_report: u32,
}

impl Throttler {
    fn new() -> Self {
        Self {
            last_tick: now_ms(),
            last_report: now_ms(),
        }
    }

    fn should_tick(&mut self) -> bool {
        let c = now_ms();
        if c < self.last_tick + 1 {
            return false;
        }
        self.last_tick = c;
        true
    }

    fn should_report(&mut self) -> bool {
        let c = now_ms();
        if c < self.last_report + 10 {
            return false;
        }
        self.last_report = c;
        true
    }
}
static mut LS_COMMAND: [Keyboard; 2] = [Keyboard::L, Keyboard::S];

#[interrupt]
fn TIM2() {
    GLOBAL_MILLISECONDS.fetch_add(1, core::sync::atomic::Ordering::Release);

    cortex_m::interrupt::free(|cs| {
        if let Some(ref mut t2) = GLOBAL_TIMER.borrow(cs).borrow_mut().deref_mut() {
            t2.clear_all_flags();
        }
    });
}

pub fn start() -> ! {
    rtt_init_print!();

    rprintln!("Testing USB functionality!");

    let keyboard_command = [Keyboard::LeftControl, Keyboard::LeftAlt, Keyboard::T];

    let dp = pac::Peripherals::take().unwrap();

    let rcc = dp.RCC.constrain();

    let clocks = rcc
        .cfgr
        .use_hse(25.MHz())
        .sysclk(48.MHz())
        .require_pll48clk()
        .freeze();

    let gpioa = dp.GPIOA.split();
    let gpiob = dp.GPIOB.split();
    let gpioc = dp.GPIOC.split();

    let usb = USB::new(
        (dp.OTG_FS_GLOBAL, dp.OTG_FS_DEVICE, dp.OTG_FS_PWRCLK),
        (gpioa.pa11, gpioa.pa12),
        &clocks,
    );

    let mut led = gpioc.pc13.into_push_pull_output_in_state(PinState::Low);

    let mut button = gpiob.pb2.into_dynamic();
    button.make_pull_down_input();
    let usb_bus = UsbBus::new(usb, unsafe { &mut EP_MEMORY });

    let mut timer = dp.TIM2.counter_us(&clocks);
    timer.start(1.millis()).unwrap();
    timer.listen(Event::Update);

    cortex_m::interrupt::free(|cs| {
        GLOBAL_TIMER.borrow(cs).borrow_mut().replace(timer);
    });

    unsafe {
        cortex_m::peripheral::NVIC::unmask(Interrupt::TIM2);
    }

    let mut keyboard = UsbHidClassBuilder::new()
        .add_device(NKROBootKeyboardConfig::default())
        .build(&usb_bus);

    let mut usb_dev = UsbDeviceBuilder::new(&usb_bus, UsbVidPid(0x16c0, 0x27dd))
        .supports_remote_wakeup(false)
        .build();

    let mut throttler = Throttler::new();

    loop {
        let is_high = button.is_high().unwrap();
        let keys = if is_high {
            keyboard_command
        } else {
            [
                Keyboard::NoEventIndicated,
                Keyboard::NoEventIndicated,
                Keyboard::NoEventIndicated,
            ]
        };

        if is_high {
            led.set_low();
        } else {
            led.set_high();
        }

        if throttler.should_report() {
            keyboard.device().write_report(keys).ok();
        }

        if throttler.should_tick() {
            keyboard.tick().unwrap();
        }

        if usb_dev.poll(&mut [&mut keyboard]) {
            match keyboard.device().read_report() {
                Ok(l) => {
                    rprintln!("REPORT: {:?}", l);
                }
                Err(UsbError::WouldBlock) => {}
                Err(e) => {
                    rprintln!("Read report error: {:?}", e);
                }
            }
        }
    }
}
