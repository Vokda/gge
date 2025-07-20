(define-module (game)
			   #:export (game_loop agents)
			   #:duplicates (check)
			   )

(use-modules ( (gge)
			  #:prefix gge:)
			 )

(define delta_string "delta: ")
(define current_player 0) 
(define players '(0 1)) ; 0 = player, 1 = world
(define i 0) ; to show delta every 60th frame
(define prev_hex -1) ; used to recolor hex from hovering
(define current_hex -1) ; hex hovered over
(define count_frame
  (lambda ()
	(set! i (+ i 1) )
	i
	)
  )

;; functions

(define (catch-all thunk)
  (with-exception-handler
	(lambda (exn)
	  (format (current-error-port)
			  "Uncaught exception: ~s\n" exn)
	  #f)
	thunk
	#:unwind? #t))

(define quit_game
  (lambda ()
	(gge:quit)))

(define game_loop
  (lambda (delta)
	(begin
	  #f
	  ) ; begin
	) ; lambda
  ) ; define

