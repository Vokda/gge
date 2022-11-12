(define-module (game)
			   #:export (game_loop)
			   #:duplicates (check)
			   )

(define delta_string "delta: ")

(define game_loop
  (lambda (delta)
	(display
	(string-append delta_string 
			   (number->string delta 10) "\n") )
	)
  )

;(define (game_loop delta) (display "hej"))
	;
	;
	;
	;)
