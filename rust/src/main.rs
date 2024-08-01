#![no_std]
#![no_main]


mod app;
use panic_halt as _;
use cortex_m_rt::entry;
#[entry]
fn main() -> ! {
    app::start();
}
