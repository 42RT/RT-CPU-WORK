#ifndef GUI_H
# define GUI_H

# include <raytracer.h>
# include <fcntl.h>
# include <dirent.h>
# include <errno.h>

# define CONTAINER gui->container[id]
# define BLOCK gui->container
# define PATH gui->path
# define BG gui->bg
# define TTF gui->ttf
# define BUTTON BLOCK[id]->button
# define TEXTBOX BLOCK[id]->textbox
# define SCROLL BLOCK[id]->scroll
# define SCROLL_B SCROLL[i]->button
# define CHECKBOX BLOCK[id]->checkbox
# define ALT_SCREEN_CENTERED 2325
# define SCANCODE event.key.keysym.scancode
# define HELP gui->help
# define PARAM gui->param
# define PARAM_SCL PARAM->scroll[i]
# define PARAM_SCL_B PARAM_SCL->button
# define PARAM_CBX PARAM->checkbox[i]
# define PARAM_BTN PARAM->button[i]
# define PARAM_GAU PARAM->gauge[i]
# define PARAM_GAU_C PARAM_GAU->cursor
# define PARAM_TXB PARAM->textbox[i]
# define PARAM_FTT PARAM->freetxt[i]
# define WIDGET gui->widget_active
# define REF t_widget_ref
# define DEF gui->def_widget

# define GUI_WIDTH gui->dest.w
# define GUI_HEIGHT gui->dest.h
# define GUI_THEME 0
# define GUI_AA 0
# define GUI_DYNAMIC 1
# define GUI_CONSTANT 0
# define GUI_FONT_BORDER_STEP 15
# define GUI_FONT_SIZE TTF->def_size
# define GUI_ALIGN_LEFT 0
# define GUI_ALIGN_MID 1
# define GUI_ALIGN_RIGHT 2
# define GUI_TEXTBOX_W GUI_WIDTH / 8
# define GUI_TEXTBOX_H 20
# define GUI_SCROLL_H 20
# define GUI_SCROLL_MAX_SHOWN 5
# define GUI_LIST_STEP 20
# define GUI_BUTTON_H 25
# define GUI_BUTTON_DEPTH 1
# define GUI_CHECKBOX_SIZE 20
# define GUI_HELP_W 360
# define GUI_HELP_H 530
# define GUI_CONTAINER_TOTAL_NB 10
# define GUI_CONTAINER_DYNAMIC_NB 1
# define GUI_CONTAINER_RESERVED 640
# define GUI_CONTAINER_RESIZED ((gui->height - \
	GUI_CONTAINER_RESERVED) / GUI_CONTAINER_DYNAMIC_NB)

typedef enum
{
				BTN,
				TXB,
				SCL,
				CBX,
				GAU,
				PRM,
				HLP,
				FTT,
				CNT
}				widget_type;

typedef struct	s_txt
{
	char		*content;
	char		*anchor;
	int			align;
}				t_txt;

typedef struct	s_ttf
{
	TTF_Font	*font;
	SDL_Texture	*texture;
	SDL_Rect	rect;
	int			h_px;
	int			w_px;
	int			def_size;
	char		*def_ttf;
	int			def_border_step;
}				t_ttf;

typedef struct	s_freetxt
{
	widget_type	nature;
	SDL_Rect	dest;
	t_txt		*txt;
	int			id;
	int			p;
	char		*tag;
}				t_freetxt;

typedef struct	s_checkbox
{
	widget_type	nature;
	SDL_Surface	*surface;
	SDL_Texture	*bmp;
	SDL_Rect	dest;
	t_txt		*txt;
	int			id;
	int			p;
	char		*tag;
	int			selected;
}				t_checkbox;

typedef struct	s_button
{
	widget_type	nature;
	SDL_Surface	*surface;
	SDL_Texture	*bmp;
	SDL_Rect	dest;
	t_txt		*txt;
	int			id;
	int			p;
	char		*action;
}				t_button;

typedef struct	s_scroll
{
	widget_type	nature;
	SDL_Surface	*surface;
	SDL_Texture	*bmp;
	SDL_Rect	dest;
	t_txt		*txt;
	int			id;
	int			p;
	char		*tag;
	t_button	*button;
	char		**value;
	int			nb_value;
	int			active_value;
	int			mod;
}				t_scroll;

typedef struct	s_textbox
{
	widget_type	nature;
	SDL_Surface	*surface;
	SDL_Texture	*bmp;
	SDL_Rect	dest;
	t_txt		*txt;
	int			id;
	int			p;
	char		*tag;
	char		*value;
	int			vlen;
	int			maxlen;
	int			min;
	int			max;
	int			edited;
}				t_textbox;

typedef struct	s_gauge
{
	widget_type	nature;
	SDL_Surface	*surface;
	SDL_Texture	*bmp;
	SDL_Rect	dest;
	t_txt		*txt;
	int			id;
	int			p;
	char		*tag;
	t_button	*cursor;
	int			min;
	int			max;
}				t_gauge;

typedef struct	s_container
{
	widget_type	nature;
	SDL_Surface	*surface;
	SDL_Texture	*bmp;
	SDL_Rect	dest;
	t_txt		*txt;
	int			up_lim;
	int			bot_lim;
	int			button_qt;
	int			scroll_qt;
	int			textbox_qt;
	int			checkbox_qt;
	int			gauge_qt;
	int			freetxt_qt;
	t_button	**button;
	t_scroll	**scroll;
	t_textbox	**textbox;
	t_checkbox	**checkbox;
	t_gauge		**gauge;
	t_freetxt	**freetxt;
}				t_container;

typedef struct	s_help
{
	widget_type	nature;
	SDL_Surface	*surface;
	SDL_Texture	*bmp;
	SDL_Rect	dest;
	int			active;
}				t_help;

typedef struct	s_param
{
	widget_type	nature;
	SDL_Surface	*surface;
	SDL_Texture	*bmp;
	SDL_Rect	dest;
	int			button_qt;
	int			scroll_qt;
	int			textbox_qt;
	int			checkbox_qt;
	int			gauge_qt;
	int			freetxt_qt;
	t_button	**button;
	t_scroll	**scroll;
	t_textbox	**textbox;
	t_checkbox	**checkbox;
	t_gauge		**gauge;
	t_freetxt	**freetxt;
	int			active;
}				t_param;

typedef struct	s_bg
{
	widget_type	nature;
	SDL_Surface	*surface;
	SDL_Texture	*bmp;
	SDL_Rect	dest;
}				t_bg;

typedef struct	s_path
{
	char		*texture;
	char		*font;
}				t_path;

typedef struct	s_widget_ref
{
	widget_type	nature;
	SDL_Surface	*surface;
	SDL_Texture	*bmp;
	SDL_Rect	dest;
	t_txt		*txt;
	int			id;
	int			p;
}				t_widget_ref;

typedef struct	s_def_widget
{
	int			txb_w;
	int			txb_h;
	char		*txb_texture;
	char		*txb_texture_selected;
	int			scl_w;
	int			scl_h;
	int			scl_max_shown;
	char		*scl_texture_head;
	char		*scl_texture_list;
	char		*sclb_texture;
	char		*sclb_texture_selected;
	int			btn_w;
	int			btn_h;
	char		*btn_texture;
	char		*btn_texture_selected;
	int			cbx_size;
	char		*cbx_texture;
	char		*cbx_texture_selected;
	int			gau_w;
	int			gau_h;
	char		*gau_texture;
	char		*gau_cursor_texture;
}				t_def_widget;

typedef struct		s_gui
{
	SDL_Window		*win;
	SDL_Renderer	*img;
	unsigned int	winID;
	SDL_Event		gui_event;
	SDL_DisplayMode	*display;
	SDL_Rect		dest;
	SDL_Color		color;
	t_color			p_color;
	t_path			*path;
	t_bg			*bg;
	t_container		**container;
	t_ttf			*ttf;
	t_help			*help;
	t_param			*param;
	t_def_widget	*def_widget;
	void			*widget_active;
	int				action;
	int				anchor_x;
	int				anchor_y;
	int				tmp_lim;
}					t_gui;

/* INIT */
t_gui		*get_gui(void);
t_gui		*gui_init(void);

/* PARSE */
void		gui_parse_builder(t_gui *gui, char *file);
void		gui_parse_param_builder(t_gui *gui, int fd, int nb);
void		gui_parse_main_builder(t_gui *gui, int fd, int nb);
void		gui_find_header(t_gui *gui, int fd, char *line);
char		**gui_get_scroll_value(t_scroll *scroll);

/* DRAW */
void		gui_pixel_put(t_gui *gui, int x, int y);
SDL_Color	gui_color(char *choice);

/* WIDGET COMMON */
void		event_widget_deselect(t_gui *gui);
void		gui_widget_draw_depth(SDL_Rect widget, int px, char *color);
void		gui_widget_draw_outline(SDL_Rect widget, int px, char *color);
void		gui_widget_draw_in_line(SDL_Rect widget, int px, char *color);
void		gui_widget_texture_get_bmp(void *widget, char *file);
void		gui_widget_display(void *widget);
void		gui_widget_write_txt(void *widget, char *color);

/* BACKGROUND */
void		gui_background_get_set_n_display(t_gui *gui);

/* CONTAINER */
void		gui_container_build(t_gui *gui, int mode, int px);

/* FONT */
void		gui_font_init(t_gui *gui, char *ttf, int size);
void		gui_font_build(t_gui *gui);

/* BUTTON */
void		gui_button_build(t_gui *gui);
void		gui_button_set(t_button *button);
void		gui_button_create_all(t_gui *gui);
void		gui_button_selected(t_gui *gui, t_button *button);
void		gui_button_free(t_button *button);
void		gui_write_button(char *text, t_button *button, char *color);

/* TEXTBOX */
t_textbox	*gui_textbox_init(void);
void		gui_textbox_build(t_gui *gui);
void		gui_textbox_set(t_textbox *textbox, SDL_Rect dest);
void		gui_textbox_get_len(t_textbox *textbox);
void		gui_textbox_create_all(t_gui *gui);
void		gui_write_textbox_value(t_gui *gui, t_textbox *textbox, char *color);
void		event_textbox_edit(t_gui *gui, t_textbox *textbox, char *color);
void		gui_get_textbox_value(t_textbox *textbox);
void		gui_textbox_value_clear(t_textbox *textbox, int len);
void		gui_textbox_load_object(t_gui *gui);

/* SCROLL */
void		gui_scroll_build(t_gui *gui);
void		gui_scroll_set(t_scroll *scroll);
void		gui_scroll_set_halign(t_scroll *scroll);
void		gui_scroll_create_all(t_gui *gui);
int			gui_scroll_value_select(t_gui *gui, SDL_Event event, t_scroll *scroll);
void		gui_scroll_toggle(t_gui *gui, t_scroll *scroll);
void		gui_scroll_free(t_scroll *scroll);
void		gui_scroll_write_list(t_gui *gui, t_scroll *scroll, int motion);
void		gui_scroll_value_write(t_gui *gui, t_scroll *scroll, char *color);
void		gui_scroll_load_object(t_gui *gui);

/* CHECKBOX */

/* GAUGE */
void		gui_gauge_normalize_value(t_gauge *gauge);

/* FREETXT */
t_freetxt	*gui_freetxt_init(void);
void		gui_freetxt_set(t_freetxt *freetxt, SDL_Rect dest);
void		gui_freetxt_write(t_freetxt *freetxt, char *color);

/* HELP */
void		gui_help_toggle(t_gui *gui);
void		gui_help_open(t_gui *gui);
void		gui_help_close(t_gui *gui);
void		gui_write_help(t_gui *gui, char *text, int align, int y);

/* PARAM */
void		gui_param_toggle(t_gui *gui);
void		gui_param_open(t_gui *gui);
void		gui_param_close(t_gui *gui);
void		gui_write_param(t_gui *gui, char *text, int aligne, int y);
void		gui_param_refresh(t_gui *gui);
t_scroll	*gui_param_scroll_init(void);
void		gui_param_scroll_set(t_scroll *scroll);
t_checkbox	*gui_param_checkbox_init(void);
void		gui_param_checkbox_set(t_checkbox *checkbox);
void		gui_param_checkbox_get_bmp(t_gui *gui, t_checkbox *checkbox, char *file);
void		gui_param_checkbox_display(t_gui *gui, t_checkbox *checkbox);
void		gui_param_checkbox_create_all(t_gui *gui);
void		gui_param_checkbox_toggle(t_gui *gui, t_checkbox *checkbox);
t_button	*gui_param_button_init(void);
t_gauge		*gui_gauge_init(void);
void		gui_gauge_set(t_gauge *gauge);

/* ERROR HANDLING */
void		gui_error(int n);

/* EVENT */
int			event_scroll_mouse_wheel(SDL_Event event, t_gui *gui);
int			event_is_scroll(SDL_Event event, t_gui *gui);
int			event_is_checkbox(SDL_Event event, t_gui *gui);
int			event_is_gauge(SDL_Event event, t_gui *gui);
int			event_is_button(SDL_Event event, t_env *env, t_gui *gui);
int			event_is_textbox(SDL_Event event, t_gui *gui);
void		event_textbox_insert(SDL_Event event, t_gui *gui, t_textbox *textbox);
void		event_scroll_mouse_over(SDL_Event event, t_gui *gui, t_scroll *scroll);

/* OTHER */
void		gui_main_refresh(t_gui *gui);
void		gui_rt_reload(t_env *e, t_gui *gui, char *scene);
void		gui_rt_reload_object(t_env *e, t_gui *gui);
void		gui_apply_object(t_gui *gui);
void		gui_apply_setting(t_gui *gui);
void		gui_save_object(t_gui *gui, t_env *e);
void		gui_anti_aliasing_set(int x, int y, int w, int h);
#endif
