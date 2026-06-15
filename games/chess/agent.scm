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

(define get_agenter_id
  (lambda ()
	agenter))

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
  '())


(define create_agent 
  (lambda (x y texture)
	(let ((id (gge:create_agent texture (gge:get_tile_from_coordinate x y))))
	  (set! agents (cons id agents))
	  id)))

(define move_selected_agent
  (lambda (tile)
	  (if (has_agent_selected)
		(begin
		  (move_agent selected_agent tile)
		  (display "Agent moved\n")
		  )
		(display "No agent selected\n")
		)
	))

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
		(if (and agents (pair? agents))
		    (begin
		      (set! selected_agent (car agents))
		      (display "select agent\n")
		      (display (string-append "Selected agent " (number->string selected_agent) "\n")))
		    (begin
		      (display "No agents on tile\n")
		      (set! selected_agent -1))))
	  (set! selected_agent -1)
	  )))


(define remove_agent
  (lambda (agent_list)
	(display "Removing agents...\n")
	(if (null? agent_list)
	  (display "No agents to remove")
	  (begin
		(display (string-append "Removing agent " (number->string (car agent_list)) "\n"))
		(gge:remove_agent (car agent_list))
	  	(display "next recursion...\n")
		(remove_agent (cdr agent_list))
		)
	  )
	))

(define clear_agents
  (lambda ()
	(remove_agent agents)
	))

(define setup_pieces
  (lambda ()
	(clear_agents)
	;(create_agent 0 1 pawn_white)
	(setup_white_pieces)
	(setup_black_pieces)
	))

(define setup_white_pieces
  (lambda ()
	(create_agent 0 1 pawn_white)
	(create_agent 1 1 pawn_white)
	(create_agent 2 1 pawn_white)
	(create_agent 3 1 pawn_white)
	(create_agent 4 1 pawn_white)
	(create_agent 5 1 pawn_white)
	(create_agent 6 1 pawn_white)
	(create_agent 7 1 pawn_white)
	(create_agent 0 0 rook_white)
	(create_agent 1 0 knight_white)
	(create_agent 2 0 bishop_white)
	(create_agent 3 0 queen_white)
	(create_agent 4 0 king_white)
	(create_agent 5 0 bishop_white)
	(create_agent 6 0 knight_white)
	(create_agent 7 0 rook_white)
	))

(define setup_black_pieces
  (lambda ()
	(create_agent 0 6 pawn_black)
	(create_agent 1 6 pawn_black)
	(create_agent 2 6 pawn_black)
	(create_agent 3 6 pawn_black)
	(create_agent 4 6 pawn_black)
	(create_agent 5 6 pawn_black)
	(create_agent 6 6 pawn_black)
	(create_agent 7 6 pawn_black)
	(create_agent 0 7 rook_black)
	(create_agent 1 7 knight_black)
	(create_agent 2 7 bishop_black)
	(create_agent 3 7 queen_black)
	(create_agent 4 7 king_black)
	(create_agent 5 7 bishop_black)
	(create_agent 6 7 knight_black)
	(create_agent 7 7 rook_black)
	))