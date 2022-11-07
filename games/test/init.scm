; test script calling all default objects and functions
; default objects begin with gge_

; remember to export the directory where the gge standard modules are located
;(use-modules (gge_scheme_std_modules gge_api))

(gge_hello)
(init_graphics "GGE Test" 640 480)
(init_events)
(init_grid 2 3 60)
(init_game_loop)

;(add_command
