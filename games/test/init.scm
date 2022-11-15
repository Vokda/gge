; test script calling all default objects and functions
; default objects begin with gge_

; remember to export the directory where the gge standard modules are located
;(use-modules (gge_api))

; a simple hello, no functionallity aside from that

(add-to-load-path (dirname (current-filename)))
(display %load-path)
(use-modules ( (game)
			  #:prefix game:)
			 )
(gge_hello)

; initialize modules wanted
; each init method returns an unsigned integer corresponding to the modules enum
(display "Initialize modules \n")
(define graphics
  (init_graphics "GGE Test" 640 480))
(define events
  (init_events))
(define grid
  (init_grid 2 3 60))
(define game_loop
  (init_game_loop))

(if (exact-integer? game_loop)
	(display "is int\n")
	(display "is NOT int\n")
	)
(display "Add commands \n")
(add_command events -1)
(add_command game_loop -1)

;(game:game_loop -1)

(display 
  (string-append  "end of: " (current-filename) "\n")
  )
