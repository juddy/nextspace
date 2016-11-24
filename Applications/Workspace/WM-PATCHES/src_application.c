--- ./WindowMaker-0.95.7/src/application.c	2015-08-11 21:41:14.000000000 +0300
+++ ./WindowMaker/src/application.c	2016-11-25 01:30:07.008472265 +0200
@@ -37,6 +37,7 @@
 #include "dock.h"
 #include "defaults.h"
 
+#include <Workspace+WindowMaker.h>
 
 /******** Local variables ********/
 
@@ -100,6 +101,13 @@
 		    wapp->app_icon->relaunching && wapp->main_window_desc->fake_group)
 			wDockFinishLaunch(wapp->app_icon);
 
+#ifdef NEXTSPACE
+		dispatch_sync(workspace_q,
+                              ^{
+                                XWApplicationDidAddWindow(wapp, wwin);
+                              });
+#endif
+                
 		return wapp;
 	}
 
@@ -140,6 +148,13 @@
 
 	create_appicon_for_application(wapp, wwin);
 
+#ifdef NEXTSPACE
+        dispatch_sync(workspace_q,
+                      ^{
+                        XWApplicationDidCreate(wapp, wwin);
+                      });
+#endif
+        
 	return wapp;
 }
 
@@ -166,6 +181,15 @@
 		return;
 	}
 
+#ifdef NEXTSPACE
+        // Must be synchronous. Otherwise XWApplicationDidDestroy crashed
+        // during access to wapp structure.
+        dispatch_sync(workspace_q,
+                      ^{
+                        XWApplicationDidDestroy(wapp);
+                      });
+#endif
+        
 	scr = wapp->main_window_desc->screen_ptr;
 
 	if (wapp == scr->wapp_list) {
