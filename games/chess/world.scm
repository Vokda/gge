; this module handles world and grid

(define-module (world)
			   #:export (get_grid))

(use-modules ( (gge)
			  #:prefix gge:)
			 )

(use-modules (system foreign))

(define grid_x 8)
(define grid_y 8)
(define grid_type 1) ; square type
(define tile_size 60)

(define grid
  (gge:init_grider grid_type grid_x grid_y tile_size 
				   (* 1 tile_size) (* 1 tile_size) ))

(define get_grid
  (lambda ()
	grid))
