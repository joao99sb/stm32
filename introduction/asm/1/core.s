// These instructions define attributes of our chip and
// the assembly language we'll use:
.syntax unified
.cpu cortex-m4
.fpu softvfp
.thumb

// Global memory locations.
.global vtable
.global reset_handler

/*
 * The actual vector table.
 * Only the size of RAM and 'reset' handler are
 * included, for simplicity.
 */
.type vtable, %object
vtable:
    .word _estack
    .word reset_handler
.size vtable, .-vtable


/*
 * The Reset handler. Called on reset.
 */
.type reset_handler, %function
reset_handler:
  // Set the stack pointer to the end of the stack.
  // The '_estack' value is defined in our linker script.
  ldr  r0, =_estack
  mov  sp, r0

  // Set some dummy values. When we see these values
  // in our debugger, we'll know that our program
  // is loaded on the chip and working.
  ; ldr  r7, =0xDEADBEEF

  mov r1, #3
  mov r2, #4
  mul r3, r1,r2
  bkpt #0
;   main_loop:
;     // Add 1 to register 'r0'.
;     ADDS r0, r0, #1

;     CMP r0, #10
;     // Loop back.
;     BNE  main_loop
.size reset_handler, .-reset_handler