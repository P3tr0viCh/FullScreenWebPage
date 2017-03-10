object Main: TMain
  Left = 0
  Top = 0
  Caption = 'FullScreenWebPage'
  ClientHeight = 240
  ClientWidth = 320
  Color = clBtnFace
  DefaultMonitor = dmPrimary
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  PopupMenu = PopupMenu
  Position = poDesigned
  Scaled = False
  SnapBuffer = 0
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnKeyUp = FormKeyUp
  OnMouseMove = FormMouseMove
  PixelsPerInch = 96
  TextHeight = 13
  object CppWebBrowser: TCppWebBrowser
    Left = 0
    Top = 0
    Width = 320
    Height = 240
    Align = alClient
    TabOrder = 0
    OnTitleChange = CppWebBrowserTitleChange
    OnDocumentComplete = CppWebBrowserDocumentComplete
    ExplicitLeft = 344
    ExplicitTop = -8
    ExplicitWidth = 784
    ExplicitHeight = 561
    ControlData = {
      4C00000013210000CE1800000000000000000000000000000000000000000000
      000000004C000000000000000000000001000000E0D057007335CF11AE690800
      2B2E126208000000000000004C0000000114020000000000C000000000000046
      8000000000000000000000000000000000000000000000000000000000000000
      00000000000000000100000000000000000000000000000000000000}
  end
  object PopupMenu: TPopupMenu
    Left = 40
    Top = 40
    object miMainFullscreen: TMenuItem
      Caption = #1055#1086#1083#1085#1099#1081' '#1101#1082#1088#1072#1085
      ShortCut = 122
      OnClick = miMainFullscreenClick
    end
    object miSeparator01: TMenuItem
      Caption = '-'
      ShortCut = 27
      OnClick = miSeparator01Click
    end
    object miMainAbout: TMenuItem
      Caption = #1054' '#1087#1088#1086#1075#1088#1072#1084#1084#1077
      OnClick = miMainAboutClick
    end
    object miSeparator02: TMenuItem
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
    Left = 120
    Top = 40
  end
end
