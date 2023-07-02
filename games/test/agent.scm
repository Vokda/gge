(define-module (agent)
			   #:export (create_agent move_agent select_agent selected_agent))

(use-modules ( (gge)
			  #:prefix gge:)
			 )

(define agenter
  (gge:init_agenter))

(define selected_agent -1)

(define placeholder
  (gge:load_image "sprites/placeholder_white.png"))

(define agents
  (list '()))


(define create_agent 
  (lambda (tile)
	(append agents (gge:create_agent placeholder tile))))

(define move_agent
  (lambda (agent tile)
	(if (and (>= agent 0) (>= tile 0))
		(begin
		  (gge:move_agent agent tile)
		  (set! selected_agent -1))
		(display "no agent selected")
		)))

(define select_agent
  (lambda (tile)
	(if (number? tile)
		(let ((agent (gge:get_agents tile)))
		  (if (pair? agent)
			  (set! selected_agent (car agent)) ;; just select first agent for now
			  -1))
		-1
	   )
	)) 
