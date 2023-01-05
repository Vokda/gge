(define-module (game)
			   #:export (game_loop)
			   #:duplicates (check)
			   )

(use-modules ( (gge)
			  #:prefix gge:)
			 )

(define delta_string "delta: ")
(define i 0) ; to show delta every 60th frame
(define prev_hex -1) ; used to recolor hex from hovering
(define current_hex -1) ; hex hovered over
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

(define mouse_on_hex?
  (lambda ()
	(cond ((> -1 (apply gge:get_hex_from_mouse (gge:get_mouse_position))) #t)
		  (else #f))
	))


(define mouse_click
  (lambda ()
	(if (mouse_on_hex?)
	  (gge:create_text 
		(number->string (apply gge:get_hex_from_mouse (gge:get_mouse_position)))
		(inexact->exact (car (gge:get_mouse_position))) 
		(inexact->exact (cadr (gge:get_mouse_position)))
		1000 ; life
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

(define mouse_hovering
  (lambda ()
	(begin
	  (set! current_hex (apply gge:get_hex_from_mouse (gge:get_mouse_position)))
	  ; color new hex
	  (gge:set_hex_color 255 0 0 current_hex)
	  ; decolor old hex
	  (if (not (= prev_hex current_hex))
		  (gge:set_hex_color 255 255 255 prev_hex))
	  (set! prev_hex current_hex)
	  )
	))

(define game_loop
  (lambda (delta)
	(begin
	  ;(if (= (modulo i 60) 0)
	  ;(display (string-append delta_string (number->string delta 10) "; i: " (number->string (count_frame) 10) "\n")))
	  (mouse_hovering)
	  (handle_events)
	  ;(if (> (count_frame) 600) #f #t ) ; quit after about 10 sec or 600 frames, should be last
	  #t
	  ) ; begin
	) ; lambda
  ) ; define

