/**********************************************************************

  Audacity: A Digital Audio Editor

  ToolManager.h

  Dominic Mazzoni
  Shane T. Mueller
  Leland Lucius

**********************************************************************/

#ifndef __AUDACITY_TOOLMANAGER__
#define __AUDACITY_TOOLMANAGER__

#include <wx/defs.h>
#include <wx/frame.h>
#include <wx/timer.h>

#include "ToolDock.h"
#include "ToolBar.h"

class wxBitmap;
class wxCommandEvent;
class wxFrame;
class wxMouseEvent;
class wxPaintEvent;
class wxPoint;
class wxRect;
class wxRegion;
class wxSize;
class wxTimer;
class wxTimerEvent;
class wxWindow;

class AudacityProject;
class ToolFrame;

////////////////////////////////////////////////////////////
/// class ToolManager
////////////////////////////////////////////////////////////

class ToolManager final : public wxEvtHandler
{

 public:

   ToolManager( AudacityProject *parent );
   ~ToolManager();

   void LayoutToolBars();
   void UpdatePrefs();

   bool IsDocked( int type );

   bool IsVisible( int type );

   void ShowHide( int type );

   void Expose( int type, bool show );

   ToolBar *GetToolBar( int type ) const;

   ToolDock *GetTopDock();
   ToolDock *GetBotDock();

   void Reset();
   void RegenerateTooltips();

 private:

   ToolBar *Float( ToolBar *t, wxPoint & pos );

   void OnTimer( wxTimerEvent & event );
   void OnMouse( wxMouseEvent & event );
   void OnCaptureLost( wxMouseCaptureLostEvent & event );
   void OnGrabber( GrabberEvent & event );
   void HandleEscapeKey();
   void DoneDragging();

   void OnIndicatorCreate( wxWindowCreateEvent & event );
   void OnIndicatorPaint( wxPaintEvent & event );

   void ReadConfig();
   void WriteConfig();
   void Updated();

   AudacityProject *mParent;

   ToolFrame *mDragWindow;
   ToolDock *mDragDock;
   ToolBar *mDragBar {};
   wxPoint mDragOffset;
   ToolBarConfiguration::Position mDragBefore {};

   wxPoint mLastPos;
   wxRect mBarPos;

   wxFrame *mIndicator;
   wxRegion *mLeft;
   wxRegion *mDown;
   wxRegion *mCurrent;

   wxTimer mTimer;
   bool mLastState;

#if defined(__WXMAC__)
   bool mTransition;
#endif

   ToolDock *mTopDock;
   ToolDock *mBotDock;

   ToolBar *mBars[ ToolBarCount ];

   wxPoint mPrevPosition {};
   ToolDock *mPrevDock {};
   ToolBarConfiguration::Position mPrevSlot
      { ToolBarConfiguration::UnspecifiedPosition };
   ToolBarConfiguration mPrevConfiguration;

 public:

   DECLARE_CLASS( ToolManager );
   DECLARE_EVENT_TABLE();
};

#endif
