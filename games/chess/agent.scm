(define-module (agent)
			   #:export (create_agent 
						  move_agent 
						  select_agent 
						  move_selected_agent 
						  has_agent_selected
						  agents
						  setup_pieces
						  ))

(use-modules ( (gge)
			  #:prefix gge:)
			 )

(use-modules (srfi srfi-9))

(define agenter
  (gge:init_agenter))

(define selected_agent -1)

; some sprites
(define pawn_white
  (gge:load_image "sprites/pawn_white.svg"))
(define pawn_black
  (gge:load_image "sprites/pawn_black.svg"))
(define rook_white
  (gge:load_image "sprites/rook_white.svg"))
(define rook_black
  (gge:load_image "sprites/rook_black.svg"))
(define knight_white
  (gge:load_image "sprites/knight_white.svg"))
(define knight_black
  (gge:load_image "sprites/knight_black.svg"))
(define bishop_white
  (gge:load_image "sprites/bishop_white.svg"))
(define bishop_black
  (gge:load_image "sprites/bishop_black.svg"))
(define queen_white
  (gge:load_image "sprites/queen_white.svg"))
(define queen_black
  (gge:load_image "sprites/queen_black.svg"))
(define king_white
  (gge:load_image "sprites/king_white.svg"))
(define king_black
  (gge:load_image "sprites/king_black.svg"))


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

(define setup_pieces
  (lambda ()
	(create_agent 0 pawn_white)
	(create_agent 1 pawn_black)
	(create_agent 2 rook_white)
	(create_agent 3 rook_black)
	(create_agent 4 knight_white)
	(create_agent 5 knight_black)
	(create_agent 6 bishop_white)
	(create_agent 7 bishop_black)
	(create_agent 8 queen_white)
	(create_agent 9 queen_black)
	(create_agent 10 king_white)
	(create_agent 11 king_black)
	))