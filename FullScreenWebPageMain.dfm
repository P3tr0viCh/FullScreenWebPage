object Main: TMain
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsNone
  Caption = 'FullScreenWebPage'
  ClientHeight = 422
  ClientWidth = 463
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PopupMenu = PopupMenu
  WindowState = wsMaximized
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnMouseMove = FormMouseMove
  PixelsPerInch = 96
  TextHeight = 13
  object CppWebBrowser: TCppWebBrowser
    Left = 0
    Top = 0
    Width = 463
    Height = 422
    Align = alClient
    TabOrder = 0
    OnTitleChange = CppWebBrowserTitleChange
    OnDocumentComplete = CppWebBrowserDocumentComplete
    ExplicitLeft = 72
    ExplicitTop = -26
    ControlData = {
      4C000000DA2F00009D2B00000000000000000000000000000000000000000000
      000000004C000000000000000000000001000000E0D057007335CF11AE690800
      2B2E126208000000000000004C0000000114020000000000C000000000000046
      8000000000000000000000000000000000000000000000000000000000000000
      00000000000000000100000000000000000000000000000000000000}
  end
  object PopupMenu: TPopupMenu
    Left = 144
    Top = 64
    object miMainAbout: TMenuItem
      Caption = #1054' '#1087#1088#1086#1075#1088#1072#1084#1084#1077
      OnClick = miMainAboutClick
    end
    object miSeparator01: TMenuItem
      Caption = '-'
    end
    object miMainClose: TMenuItem
      Caption = #1047#1072#1082#1088#1099#1090#1100
      ShortCut = 32883
      OnClick = miMainCloseClick
    end
  end
  object TimerHideCursor: TTimer
    Enabled = False
    Interval = 3000
    OnTimer = TimerHideCursorTimer
    Left = 248
    Top = 64
  end
end
