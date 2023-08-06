(define-module (agent)
			   #:export (create_agent 
						  move_agent 
						  select_agent 
						  move_selected_agent 
						  has_agent_selected
						  agents
						  ))

(use-modules ( (gge)
			  #:prefix gge:)
			 )

(use-modules (srfi srfi-9))

(define agenter
  (gge:init_agenter))

(define selected_agent -1)

; some sprites
(define placeholder
  (gge:load_image "sprites/placeholder_white.png"))

(define triangle_up
  (gge:load_image "sprites/triangle_up.png"))

(define triangle_down
  (gge:load_image "sprites/triangle_down.png"))

(define triangle_down
  (gge:load_image "sprites/cylinder.png"))

;(define-record-type "agent" 
;				  (make-agent index tile texture)
;				  agent?
;				  (index	agent-index)
;				  (tile		agent-tile)
;				  (texture	agent-texture))
(define agents
  (list '()))


(define create_agent 
  (lambda (tile texture)
	(append agents (gge:create_agent texture tile))))

(define move_selected_agent
  (lambda (tile)
	(move_agent selected_agent tile)))

(define move_agent
  (lambda (agent tile)
	(let (( a selected_agent))
	  (if (and (>= agent 0) (>= tile 0))
		(begin
		  (gge:move_agent agent tile)
		  (set! selected_agent -1)
		  a)
		))))

(define has_agent_selected
  (lambda ()
	(if (not (= selected_agent -1))
	  #t
	  #f)))

(define select_agent
  (lambda (tile)
	(if (number? tile)
	  (let ((agents (gge:get_agents tile)))
		(if (pair? agents)
		  (set! selected_agent (car agents)) ;; just select first agent for now
		  (set! selected_agent -1)
		  ))
	  (set! selected_agent -1)
	  )))
