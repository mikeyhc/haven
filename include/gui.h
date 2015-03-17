/* gui.h
 * an interface for high level control of the GUI
 *
 * author <mikeyhc@atmosia.net>
 */

#ifndef _HAVEN_GUI_H
#define _HAVEN_GUI_H

char initialize_gui(void);
void quit_gui(void);

void render_screen(void);
void gl_swap_window(void);

#endif /* _HAVEN_GUI_H */
