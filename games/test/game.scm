(define-module (game)
			   #:export (game_loop agents)
			   #:duplicates (check)
			   )

(use-modules ( (gge)
			  #:prefix gge:)
			 )

(use-modules ( (agent)
			  #:prefix agent:))
(use-modules (system foreign))

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

(define mouse_on_hex?
  (lambda (mouse_pos)
	(begin 
	  (if (< -1 (apply gge:get_tile_from_mouse mouse_pos))
		  #t
		  #f
		  ))))

(define display_hex
  (lambda (hex)
	(if (null? hex) (display "no hex display")
	(gge:create_text 
	  (pointer->string (gge:get_tile_custom_data 
						 hex
						 "name"
						 )) ; text ( hex data 'name)
	  ;(number->string (apply gge:get_hex_from_mouse (gge:get_mouse_position))) ; text (# of hex)
	  (inexact->exact (car (gge:get_mouse_position))) ; x position
	  (inexact->exact (cadr (gge:get_mouse_position))) ; y position
	  1000 ; life
	  0)); viewport
	))

(define select_hex
  (lambda (mouse_pos)
	(if (null? mouse_pos)
		-1
		(begin
		  (display "select_hex")
		  (display  mouse_pos)
		  (display "\n")
		  (apply gge:get_tile_from_mouse mouse_pos)
		  )
		)
  ))

(define mouse_click
	(lambda ()
	  (let ( (hex (select_hex (gge:get_mouse_position))) )
		(if (>= hex 0)
			  ;(display_hex hex)
			  (if (agent:has_agent_selected)
				(agent:move_selected_agent hex)
				(agent:select_agent hex)
				)))))

(define handle_events
  (let ((event (gge:get_next_event))) 
	(lambda () 
	  ;(display "handle event\n")
		(set! event (gge:get_next_event))
			(when (not (= event 0))
			  (cond ((= event 113) (quit_game))
					((= event 1) (mouse_click ))
			  (else (display (string-append "\nevent " (number->string event)))))
			  (handle_events)
			  );t
	  )))

(define mouse_hovering
  (lambda ()
	(let (( mouse_pos (gge:get_mouse_position) ))
	  (begin
		(set! current_hex (apply gge:get_tile_from_mouse mouse_pos))
		; color new hex
		(gge:set_tile_color 255 0 0 current_hex)
		; decolor old hex
		(if (not (= prev_hex current_hex))
			(gge:set_tile_color 255 255 255 prev_hex))
		(set! prev_hex current_hex)
		))
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

