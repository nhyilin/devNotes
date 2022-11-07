; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CFirstView
LastTemplate=CFormView
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Splitter.h"
LastPage=0

ClassCount=6
Class1=CSplitterApp
Class2=CSplitterDoc
Class3=CSplitterView
Class4=CMainFrame

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class5=CAboutDlg
Class6=CFirstView
Resource3=IDD_DIALOG

[CLS:CSplitterApp]
Type=0
HeaderFile=Splitter.h
ImplementationFile=Splitter.cpp
Filter=N

[CLS:CSplitterDoc]
Type=0
HeaderFile=SplitterDoc.h
ImplementationFile=SplitterDoc.cpp
Filter=N

[CLS:CSplitterView]
Type=0
HeaderFile=SplitterView.h
ImplementationFile=SplitterView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=CSplitterView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=CMainFrame




[CLS:CAboutDlg]
Type=0
HeaderFile=Splitter.cpp
ImplementationFile=Splitter.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_APP_ABOUT
CommandCount=16

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[DLG:IDD_DIALOG]
Type=1
Class=CFirstView
ControlCount=8
Control1=IDC_STATIC,static,1342308352
Control2=IDC_SLIDER2,msctls_trackbar32,1342242840
Control3=IDC_BUTTON1,button,1342242816
Control4=IDC_BUTTON2,button,1342242816
Control5=IDC_STATIC,button,1342177287
Control6=IDC_YES,button,1342178057
Control7=IDC_NO,button,1342178057
Control8=IDC_STATIC,static,1342308352

[CLS:CFirstView]
Type=0
HeaderFile=FirstView.h
ImplementationFile=FirstView.cpp
BaseClass=CFormView
Filter=D
LastObject=IDC_YES
VirtualFilter=VWC

