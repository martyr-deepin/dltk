/* GTK - The GIMP Toolkit
 * Copyright (C) 1995-1997 Peter Mattis, Spencer Kimball and Josh MacDonald
 *
 * GTK Calendar Widget
 * Copyright (C) 1998 Cesar Miquel and Shawn T. Amundson
 * DTK Calendar Widget
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

#ifndef __DTK_CALENDAR_H__
#define __DTK_CALENDAR_H__

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define DTK_TYPE_CALENDAR                  (dtk_calendar_get_type ())
#define DTK_CALENDAR(obj)                  (G_TYPE_CHECK_INSTANCE_CAST ((obj), DTK_TYPE_CALENDAR, DtkCalendar))
#define DTK_CALENDAR_CLASS(klass)          (G_TYPE_CHECK_CLASS_CAST ((klass), DTK_TYPE_CALENDAR, DtkCalendarClass))
#define DTK_IS_CALENDAR(obj)               (G_TYPE_CHECK_INSTANCE_TYPE ((obj), DTK_TYPE_CALENDAR))
#define DTK_IS_CALENDAR_CLASS(klass)       (G_TYPE_CHECK_CLASS_TYPE ((klass), DTK_TYPE_CALENDAR))
#define DTK_CALENDAR_GET_CLASS(obj)        (G_TYPE_INSTANCE_GET_CLASS ((obj), DTK_TYPE_CALENDAR, DtkCalendarClass))


typedef struct _DtkCalendar	       DtkCalendar;
typedef struct _DtkCalendarClass       DtkCalendarClass;

typedef struct _DtkCalendarPrivate     DtkCalendarPrivate;

/**
 * DtkCalendarDisplayOptions:
 * @DTK_CALENDAR_SHOW_HEADING: Specifies that the month and year should be displayed.
 * @DTK_CALENDAR_SHOW_DAY_NAMES: Specifies that three letter day descriptions should be present.
 * @DTK_CALENDAR_NO_MONTH_CHANGE: Prevents the user from switching months with the calendar.
 * @DTK_CALENDAR_SHOW_WEEK_NUMBERS: Displays each week numbers of the current year, down the
 * left side of the calendar.
 * @DTK_CALENDAR_WEEK_START_MONDAY: Since GTK+ 2.4, this option is deprecated and ignored by GTK+.
 * The information on which day the calendar week starts is derived from the locale.
 * @DTK_CALENDAR_SHOW_DETAILS: Just show an indicator, not the full details
 * text when details are provided. See dtk_calendar_set_detail_func().
 *
 * These options can be used to influence the display and behaviour of a #DtkCalendar.
 */
typedef enum
{
  DTK_CALENDAR_SHOW_HEADING		= 1 << 0,
  DTK_CALENDAR_SHOW_DAY_NAMES		= 1 << 1,
  DTK_CALENDAR_NO_MONTH_CHANGE		= 1 << 2,
  DTK_CALENDAR_SHOW_WEEK_NUMBERS	= 1 << 3,
  DTK_CALENDAR_WEEK_START_MONDAY	= 1 << 4,
  DTK_CALENDAR_SHOW_DETAILS		= 1 << 5
} DtkCalendarDisplayOptions;

/**
 * DtkCalendarDetailFunc:
 * @calendar: a #DtkCalendar.
 * @year: the year for which details are needed.
 * @month: the month for which details are needed.
 * @day: the day of @month for which details are needed.
 * @user_data: the data passed with dtk_calendar_set_detail_func().
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
typedef gchar* (*DtkCalendarDetailFunc) (DtkCalendar *calendar,
                                         guint        year,
                                         guint        month,
                                         guint        day,
                                         gpointer     user_data);

struct _DtkCalendar
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
  DtkCalendarDisplayOptions  GSEAL (display_flags);
  GdkColor GSEAL (marked_date_color[31]);
  
  GdkGC *GSEAL (gc);			/* unused */
  GdkGC *GSEAL (xor_gc);		/* unused */

  gint GSEAL (focus_row);
  gint GSEAL (focus_col);

  gint GSEAL (highlight_row);
  gint GSEAL (highlight_col);
  
  DtkCalendarPrivate *GSEAL (priv);
  gchar GSEAL (grow_space [32]);

  /* Padding for future expansion */
  void (*_gtk_reserved1) (void);
  void (*_gtk_reserved2) (void);
  void (*_gtk_reserved3) (void);
  void (*_gtk_reserved4) (void);
};

struct _DtkCalendarClass
{
  GtkWidgetClass parent_class;
  
  /* Signal handlers */
  void (* month_changed)		(DtkCalendar *calendar);
  void (* day_selected)			(DtkCalendar *calendar);
  void (* day_selected_double_click)	(DtkCalendar *calendar);
  void (* prev_month)			(DtkCalendar *calendar);
  void (* next_month)			(DtkCalendar *calendar);
  void (* prev_year)			(DtkCalendar *calendar);
  void (* next_year)			(DtkCalendar *calendar);
  
};


GType	   dtk_calendar_get_type	(void) G_GNUC_CONST;
GtkWidget* dtk_calendar_new		(void);

gboolean   dtk_calendar_select_month	(DtkCalendar *calendar,
					 guint	      month,
					 guint	      year);
void	   dtk_calendar_select_day	(DtkCalendar *calendar,
					 guint	      day);

gboolean   dtk_calendar_mark_day	(DtkCalendar *calendar,
					 guint	      day);
gboolean   dtk_calendar_unmark_day	(DtkCalendar *calendar,
					 guint	      day);
void	   dtk_calendar_clear_marks	(DtkCalendar *calendar);


void	   dtk_calendar_set_display_options (DtkCalendar    	      *calendar,
					     DtkCalendarDisplayOptions flags);
DtkCalendarDisplayOptions
           dtk_calendar_get_display_options (DtkCalendar   	      *calendar);
#ifndef GTK_DISABLE_DEPRECATED
void	   dtk_calendar_display_options (DtkCalendar		  *calendar,
					 DtkCalendarDisplayOptions flags);
#endif

void	   dtk_calendar_get_date	(DtkCalendar *calendar, 
					 guint	     *year,
					 guint	     *month,
					 guint	     *day);

void       dtk_calendar_set_detail_func (DtkCalendar           *calendar,
                                         DtkCalendarDetailFunc  func,
                                         gpointer               data,
                                         GDestroyNotify         destroy);

void       dtk_calendar_set_detail_width_chars (DtkCalendar    *calendar,
                                                gint            chars);
void       dtk_calendar_set_detail_height_rows (DtkCalendar    *calendar,
                                                gint            rows);

gint       dtk_calendar_get_detail_width_chars (DtkCalendar    *calendar);
gint       dtk_calendar_get_detail_height_rows (DtkCalendar    *calendar);

#ifndef GTK_DISABLE_DEPRECATED
void	   dtk_calendar_freeze		(DtkCalendar *calendar);
void	   dtk_calendar_thaw		(DtkCalendar *calendar);
#endif

G_END_DECLS

#endif /* __DTK_CALENDAR_H__ */
