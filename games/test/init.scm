; test script calling all default objects and functions
; default objects begin with gge_

; remember to export the directory where the gge standard modules are located
;(use-modules (gge_api))

; a simple hello, no functionallity aside from that

(use-modules (system foreign))

(add-to-load-path (dirname (current-filename)))
(display %load-path)

(use-modules ( (gge)
			  #:prefix gge:)
			 )

(newline)
(display (module-uses (current-module)))
(newline)



(gge:hello)

; initialize modules wanted
; each init method returns an unsigned integer corresponding to the modules enum
(display "Initialize modules \n")
(define graphics
  (gge:init_graphics "GGE Test" 640 480))
(define events
  (gge:init_events))
(define grid_x 2)
(define grid_y 3)
(define grid
  (gge:init_grid grid_x grid_y 60))
(define game_loop
  (gge:init_game_loop))
(define texter
  (gge:init_texter))

(display "Add commands \n")
; add_command <module to execute command> <command number, -1 = there is only one to pick (change to 0?)> <id to module used as parameter, 0 = None>
(gge:add_command graphics 0 0) ; clear screen
(gge:add_command events -1 0)
(gge:add_command game_loop -1 0)
(gge:add_command texter 0 0) ; ticker
(gge:add_command graphics 1 grid) ; draw
(gge:add_command graphics 1 texter)
(gge:add_command graphics 2 0) ;  render

; set data to hexes
(do ((i 0 (1+ i)))
  ((>= i (* grid_x grid_y)))
   (gge:set_hex_custom_data i "name" (string->pointer (string-append "hex " (number->string i)) ) ))
