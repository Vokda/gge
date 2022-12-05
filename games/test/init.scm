; test script calling all default objects and functions
; default objects begin with gge_

; remember to export the directory where the gge standard modules are located
;(use-modules (gge_api))

; a simple hello, no functionallity aside from that

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
(define grid
  (gge:init_grid 2 3 60))
(define game_loop
  (gge:init_game_loop))

(display "Add commands \n")
(gge:add_command events -1)
(gge:add_command game_loop -1)
