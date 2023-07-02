; useful default  functions

(define-module (gge)
	#:export (gge_hello)
	)

(define (gge_hello) (display "GGE says hello!") )

(define mouse_on_hex?
  (lambda ()
	(if ((< -1 (apply gge:get_tile_from_mouse (gge:get_mouse_position))) #t)
		  #f)))
