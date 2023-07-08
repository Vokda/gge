; this module handles world and grid

(define-module (world)
			   #:export (get_grid))

(use-modules ( (gge)
			  #:prefix gge:)
			 )

(use-modules (system foreign))

(define grid_x 2)
(define grid_y 3)
(define grid_type 0) ; hex type
(define tile_size 60)

(define grid
  (gge:init_grider grid_type grid_x grid_y tile_size tile_size   tile_size ))

(define get_grid
  (lambda ()
	grid))

; set data to hexes
(do ((i 0 (1+ i)))
  ((>= i (* grid_x grid_y)))
   (gge:set_tile_custom_data i "name" (string->pointer (string-append "hex " (number->string i)))))

