(define-module (game)
			   #:export (game_loop)
			   #:duplicates (check)
			   )

(use-modules ( (gge)
			  #:prefix gge:)
			 )

(define delta_string "delta: ")
(define i 0) ; to show delta every 60th frame
(define count_frame
  (lambda ()
	(set! i (+ i 1) )
	i
	)
  )

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

(define mouse_click
  (lambda ()
	(begin
	  (gge:create_text 
		"Click" 
		(inexact->exact (car (gge:get_mouse_position))) 
		(inexact->exact (cadr (gge:get_mouse_position)))
		100 ; life
		0) ; viewport
	  )
	))

(define handle_events
  (let ((event (gge:get_next_event))) ; does this do something?
	(lambda () 
		(set! event (gge:get_next_event))
			(when (not (= event 0))
			  (cond ((= event 113) (quit_game))
					((= event 1) (mouse_click))
			  (else (display (string-append "\nevent " (number->string event)))))
			  (handle_events)
			  );t
	  )))

(make-record-type "coord" '(x y))

(define game_loop
  (lambda (delta)
	(begin
	  ;(if (= (modulo i 60) 0)
	  ;(display (string-append delta_string (number->string delta 10) "; i: " (number->string (count_frame) 10) "\n")))
	  (handle_events)
	  ;(if (> (count_frame) 600) #f #t ) ; quit after about 10 sec or 600 frames, should be last
	  #t
	  ) ; begin
	) ; lambda
  ) ; define

