; test script calling all default objects and functions
; default objects begin with gge_

; remember to export the directory where the gge standard modules are located
;(use-modules (gge_api))

;; debug stuff
;(debug-enable 'backtrace)
;(debug-enable 'stack)
;(debug-enable 'trace)


(add-to-load-path (dirname (current-filename)))
(display %load-path)

(use-modules ( (gge)
			  #:prefix gge:)
			 )

(newline)
(display (module-uses (current-module)))
(newline)

; a simple hello, no functionallity aside from that
(gge:hello)

; initialize modules wanted
; each init method returns an unsigned integer corresponding to the modules enum
(display "Initialize modules \n")
(define graphics
  (gge:init_graphics "chess" 800 600))
(define events
  (gge:init_events))
(define gge_game_loop
  (gge:init_game_loop))
(define texter
  (gge:init_texter))
(define spriter
  (gge:init_spriter))
(define gui
  (gge:init_gui))
(define shaper
  (gge:initialize_gge_module 9))

;(define scroller_id 4) ; TODO special case until I fix the enum situation
;(define scroller
  ;(gge:initialize_gge_module scroller_id))

(use-modules ( (world)
			 #:prefix world:)
			)
(use-modules ( (agent)
			  #:prefix agent:)
			 )

(display "Add commands \n")
; add_command <module to execute command> <command number, -1 = there is only one to pick (change to 0?)> <id to module used as parameter, 0 = None>
; could it be less intuitive?
(gge:hello)
(gge:add_command graphics 0 0) ; clear screen
(gge:hello)
(gge:add_command events -1 0)
(gge:add_command gge_game_loop -1 0)
; draw stuff
(gge:add_command graphics 1 (world:get_grid) )
(gge:add_command graphics 1 texter)
(gge:add_command graphics 1 spriter)
(gge:add_command graphics 1 gui)
(gge:add_command graphics 2 0) ;  render

; gui stuff
(gge:create_button "New Game"  (lambda () (agent:setup_pieces) ))
(gge:create_button "Quit" (lambda () (gge:quit)))	