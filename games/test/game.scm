(define-module (game)
			   #:export (game_loop)
			   #:duplicates (check)
			   )

(define delta_string "delta: ")
(define i 0) ; to show delta every 60th frame
(define count_frame
  (lambda ()
	(set! i (+ i 1) )
	i
	)
  )

(define game_loop
		(lambda (delta)
		  (begin
			(if (= (modulo i 60) 0)
				(display (string-append delta_string (number->string delta 10) "; i: " (number->string (count_frame) 10) "\n")) 
				)

			(game:gge_hello)

			(if (> (count_frame) 600) #f #t ) ; quit after about 10 sec or 600 frames, should be last

			) ; end begin
		  )
  )
