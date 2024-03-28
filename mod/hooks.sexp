(;; just don't choose something that depends on pc and we should be good
 ;; i.e any relative branch
 ;; start of while loop in void Global::zGameLoop(void)
 ;; 800b9cf4 38 00 00 00     li         r0,0x0
 ((address 0x800b9cf4)
  (function_name game_loop_hook))
 ((address 0x800baa2c)
  (function_name end_of_render)))
