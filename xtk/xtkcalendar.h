/* GTK - The GIMP Toolkit
 * Copyright (C) 1995-1997 Peter Mattis, Spencer Kimball and Josh MacDonald
 *
 * GTK Calendar Widget
 * Copyright (C) 1998 Cesar Miquel and Shawn T. Amundson
 *
 * XTK Calendar Widget
 * Copyright (C) 2013 Deepin, Inc.
 *               2013 Zhai Xiang <zhaixiang@linuxdeepin.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/*
 * Modified by the GTK+ Team and others 1997-2000.  See the AUTHORS
 * file for a list of people on the GTK+ Team.  See the ChangeLog
 * files for a list of changes.  These files are distributed with
 * GTK+ at ftp://ftp.gtk.org/pub/gtk/.
 */

#ifndef __XTK_CALENDAR_H__
#define __XTK_CALENDAR_H__

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define XTK_TYPE_CALENDAR                  (xtk_calendar_get_type ())
#define XTK_CALENDAR(obj)                  (G_TYPE_CHECK_INSTANCE_CAST ((obj), XTK_TYPE_CALENDAR, XtkCalendar))
#define XTK_CALENDAR_CLASS(klass)          (G_TYPE_CHECK_CLASS_CAST ((klass), XTK_TYPE_CALENDAR, XtkCalendarClass))
#define XTK_IS_CALENDAR(obj)               (G_TYPE_CHECK_INSTANCE_TYPE ((obj), XTK_TYPE_CALENDAR))
#define XTK_IS_CALENDAR_CLASS(klass)       (G_TYPE_CHECK_CLASS_TYPE ((klass), XTK_TYPE_CALENDAR))
#define XTK_CALENDAR_GET_CLASS(obj)        (G_TYPE_INSTANCE_GET_CLASS ((obj), XTK_TYPE_CALENDAR, XtkCalendarClass))


typedef struct _XtkCalendar	       XtkCalendar;
typedef struct _XtkCalendarClass       XtkCalendarClass;

typedef struct _XtkCalendarPrivate     XtkCalendarPrivate;

/**
 * XtkCalendarDisplayOptions:
 * @XTK_CALENDAR_SHOW_HEADING: Specifies that the month and year should be displayed.
 * @XTK_CALENDAR_SHOW_DAY_NAMES: Specifies that three letter day descriptions should be present.
 * @XTK_CALENDAR_NO_MONTH_CHANGE: Prevents the user from switching months with the calendar.
 * @XTK_CALENDAR_SHOW_WEEK_NUMBERS: Displays each week numbers of the current year, down the
 * left side of the calendar.
 * @XTK_CALENDAR_WEEK_START_MONDAY: Since GTK+ 2.4, this option is deprecated and ignored by GTK+.
 * The information on which day the calendar week starts is derived from the locale.
 * @XTK_CALENDAR_SHOW_DETAILS: Just show an indicator, not the full details
 * text when details are provided. See xtk_calendar_set_detail_func().
 *
 * These options can be used to influence the display and behaviour of a #XtkCalendar.
 */
typedef enum
{
  XTK_CALENDAR_SHOW_HEADING		= 1 << 0,
  XTK_CALENDAR_SHOW_DAY_NAMES		= 1 << 1,
  XTK_CALENDAR_NO_MONTH_CHANGE		= 1 << 2,
  XTK_CALENDAR_SHOW_WEEK_NUMBERS	= 1 << 3,
  XTK_CALENDAR_WEEK_START_MONDAY	= 1 << 4,
  XTK_CALENDAR_SHOW_DETAILS		= 1 << 5
} XtkCalendarDisplayOptions;

/**
 * XtkCalendarDetailFunc:
 * @calendar: a #XtkCalendar.
 * @year: the year for which details are needed.
 * @month: the month for which details are needed.
 * @day: the day of @month for which details are needed.
 * @user_data: the data passed with xtk_calendar_set_detail_func().
 *
 * This kind of functions provide Pango markup with detail information for the
 * specified day. Examples for such details are holidays or appointments. The
 * function returns %NULL when no information is available.
 *
 * Since: 2.14
 *
 * Return value: Newly allocated string with Pango markup with details
 * for the specified day, or %NULL.
 */
typedef gchar* (*XtkCalendarDetailFunc) (XtkCalendar *calendar,
                                         guint        year,
                                         guint        month,
                                         guint        day,
                                         gpointer     user_data);

struct _XtkCalendar
{
  GtkWidget widget;
  
  GtkStyle  *GSEAL (header_style);
  GtkStyle  *GSEAL (label_style);
  
  gint GSEAL (month);
  gint GSEAL (year);
  gint GSEAL (selected_day);
  
  gint GSEAL (day_month[6][7]);
  gint GSEAL (day[6][7]);
  
  gint GSEAL (num_marked_dates);
  gint GSEAL (marked_date[31]);
  XtkCalendarDisplayOptions  GSEAL (display_flags);
  GdkColor GSEAL (marked_date_color[31]);
  
  GdkGC *GSEAL (gc);			/* unused */
  GdkGC *GSEAL (xor_gc);		/* unused */

  gint GSEAL (focus_row);
  gint GSEAL (focus_col);

  gint GSEAL (highlight_row);
  gint GSEAL (highlight_col);
  
  XtkCalendarPrivate *GSEAL (priv);
  gchar GSEAL (grow_space [32]);

  /* Padding for future expansion */
  void (*_gtk_reserved1) (void);
  void (*_gtk_reserved2) (void);
  void (*_gtk_reserved3) (void);
  void (*_gtk_reserved4) (void);
};

struct _XtkCalendarClass
{
  GtkWidgetClass parent_class;
  
  /* Signal handlers */
  void (* month_changed)		(XtkCalendar *calendar);
  void (* day_selected)			(XtkCalendar *calendar);
  void (* day_selected_double_click)	(XtkCalendar *calendar);
  void (* prev_month)			(XtkCalendar *calendar);
  void (* next_month)			(XtkCalendar *calendar);
  void (* prev_year)			(XtkCalendar *calendar);
  void (* next_year)			(XtkCalendar *calendar);
  
};


GType	   xtk_calendar_get_type	(void) G_GNUC_CONST;
GtkWidget* xtk_calendar_new		(void);

gboolean   xtk_calendar_select_month	(XtkCalendar *calendar,
					 guint	      month,
					 guint	      year);
void	   xtk_calendar_select_day	(XtkCalendar *calendar,
					 guint	      day);

gboolean   xtk_calendar_mark_day	(XtkCalendar *calendar,
					 guint	      day);
gboolean   xtk_calendar_unmark_day	(XtkCalendar *calendar,
					 guint	      day);
void	   xtk_calendar_clear_marks	(XtkCalendar *calendar);


void	   xtk_calendar_set_display_options (XtkCalendar    	      *calendar,
					     XtkCalendarDisplayOptions flags);
XtkCalendarDisplayOptions
           xtk_calendar_get_display_options (XtkCalendar   	      *calendar);
#ifndef GTK_DISABLE_DEPRECATED
void	   xtk_calendar_display_options (XtkCalendar		  *calendar,
					 XtkCalendarDisplayOptions flags);
#endif

void	   xtk_calendar_get_date	(XtkCalendar *calendar, 
					 guint	     *year,
					 guint	     *month,
					 guint	     *day);

void       xtk_calendar_set_detail_func (XtkCalendar           *calendar,
                                         XtkCalendarDetailFunc  func,
                                         gpointer               data,
                                         GDestroyNotify         destroy);

void       xtk_calendar_set_detail_width_chars (XtkCalendar    *calendar,
                                                gint            chars);
void       xtk_calendar_set_detail_height_rows (XtkCalendar    *calendar,
                                                gint            rows);

gint       xtk_calendar_get_detail_width_chars (XtkCalendar    *calendar);
gint       xtk_calendar_get_detail_height_rows (XtkCalendar    *calendar);

#ifndef GTK_DISABLE_DEPRECATED
void	   xtk_calendar_freeze		(XtkCalendar *calendar);
void	   xtk_calendar_thaw		(XtkCalendar *calendar);
#endif

G_END_DECLS

#endif /* __XTK_CALENDAR_H__ */
