; test script calling all default objects and functions
; default objects begin with gge_

; remember to export the directory where the gge standard modules are located
;(use-modules (gge_scheme_std_modules gge_api))
(gge_hello)
(gge_init_module 1 "GGE Test" 640 480)


;print(gge_api.hello())
;
;var graphics_module = gge_api.init_graphics("test name", 800, 600) // should change the default 
;gge_api.init_events()
;gge_api.init_grid(2, 3, 60)
;
;// command order
;gge_api.add_command(graphics_module, :qa
;gge_api.add_command("graphics.clear_screen()")
;gge_api.add_command("scroller.scroll(grid)")
;gge_api.add_command("texter.tick()")
;gge_api.add_command("graphics.draw(grid)")
;gge_api.add_command("graphics.draw(shape)")
;gge_api.add_command("graphics.draw(texter)")
;gge_api.add_command("graphics.render()")
;// ^ oh wow how intuitive ^
;
;
;//print(gge_api.info())
;// view ports 
;// main = 0, bar = 1, side = 2
;//gge_api.create_text("Top bar text", 0)
;gge_api.create_text(
;	"advanced temporary red text %i", 
;	[255,255,255,255],
;	//stl_vector_int([200,200,-1,-1]),
;	[0,0,-1,-1],
;	-1,
;	1)
;// create instance of game object
;// containing game loop and event handle
;var game = Game()
;
;// return name of game object
;return "game"
