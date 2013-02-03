object frmMain: TfrmMain
  Left = 691
  Top = 272
  Width = 400
  Height = 600
  BorderIcons = [biSystemMenu, biMinimize]
  Caption = 'QstTree'
  Color = clBtnFace
  Constraints.MinHeight = 600
  Constraints.MinWidth = 200
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  OnKeyUp = FormKeyUp
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object sptTnB: TSplitter
    Left = 0
    Top = 449
    Width = 392
    Height = 3
    Cursor = crVSplit
    Align = alTop
  end
  object lstTree: TVirtualStringTree
    Left = 0
    Top = 0
    Width = 392
    Height = 449
    Align = alTop
    Header.AutoSizeIndex = 0
    Header.DefaultHeight = 17
    Header.Font.Charset = DEFAULT_CHARSET
    Header.Font.Color = clWindowText
    Header.Font.Height = -11
    Header.Font.Name = 'MS Sans Serif'
    Header.Font.Style = []
    Header.MainColumn = -1
    Images = imgIcoLst
    TabOrder = 0
    OnChange = lstTreeChange
    OnFreeNode = lstTreeFreeNode
    OnGetText = lstTreeGetText
    OnPaintText = lstTreePaintText
    OnGetImageIndex = lstTreeGetImageIndex
    Columns = <>
  end
  object txtInfo: TMemo
    Left = 0
    Top = 452
    Width = 392
    Height = 118
    Align = alClient
    ReadOnly = True
    ScrollBars = ssBoth
    TabOrder = 1
    WordWrap = False
  end
  object themeMgr: TThemeManager
    Left = 16
    Top = 16
  end
  object dlgOpen: TOpenDialog
    Filter = '*.xml|*.xml'
    InitialDir = '.'
    Options = [ofNoChangeDir, ofPathMustExist, ofFileMustExist, ofEnableSizing]
    Title = 'Open XML file'
    Left = 48
    Top = 16
  end
  object imgIcoLst: TImageList
    Left = 80
    Top = 16
    Bitmap = {
      494C010104000900040010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000003000000001002000000000000030
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000D3CECBFF9F93
      8DFF7C6E65FF736259FF736158FF736158FF736158FF736158FF736158FF7361
      58FF736259FF7C6E65FF9F938DFFD3CECBFF00000000F5F5F5FFDEDEDEFFD5D5
      D5FFD5D5D5FFD5D5D5FFD5D5D5FFD5D5D5FFD5D5D5FFD5D5D5FFD5D5D5FFD5D5
      D5FFD5D5D5FFD5D5D5FFDEDEDEFFF5F5F5FFF8F8F8FFE2E2E2FFD0D0D0FFD4D4
      D4FFE0E0E0FFEBEBEBFFF5F5F5FFFDFDFDFF377224FF7C7C7CFF7C7C7CFFC4C4
      C4FFF4F4F4FF00000000000000000000000000000000CFC7C3FFC5BDB8FFC2B9
      B4FFC2B8B3FFC2B8B3FFC1B7B3FFC1B7B2FFC0B6B2FFC0B6B2FFC1B7B3FFC5BC
      B8FFDBD5D3FFF6F4F4FFFDFCFCFFFEFEFEFF0000000000000000AE7B6EFFD9AD
      9DFFD6A89AFFD3A698FFD2A497FFCCA199FFC99E97FFC69C96FFC49995FFC196
      93FFB6918BFFB88E8BFF7E6F66FFC4BBB9FFF5F5F5FFC7C7C7FF828282FF6B6B
      6BFF6B6B6BFF6B6B6BFF6B6B6BFF6B6B6BFF6B6B6BFF6B6B6BFF6B6B6BFF6B6B
      6BFF6B6B6BFF6B6B6BFF828282FFC7C7C7FFDDE3E6FF9EAAB1FF818181FF7C7C
      7CFF8F8F8FFFA6A6A6FFBCBCBCFFCBCBCBFF377224FF377224FF4C4C4CFF7C7C
      7CFFC4C4C4FFF4F4F4FF0000000000000000E3DBD5FF958378FF89756AFF846F
      65FF836E63FF826D63FF816B62FF7F6A61FF7F6960FF7E685FFF7E675FFF7C69
      60FF9E8F88FFECEAE9FFFAFAFAFFFEFEFEFF0000000000000000B58272FFFCE1
      CBFFFBE0C8FFFBDEC4FFFBDCC2FFFADABEFFFAD8BBFFFBD7B8FFFAD4B4FFF9D2
      B1FFFAD0AEFFEEBDA5FF736259FFC0B8B4FFDEDEDEFF1C82B5FF1A80B3FF177D
      B0FF157BAEFF1278ABFF0F75A8FF0C72A5FF0A70A3FF076DA0FF056B9EFF0369
      9CFF01679AFF006699FF4B4B4BFF828282FF72A4BEFF56A9CCFF107AA7FF1662
      85FF2D5970FF4A5D67FF666666FF6E6E6EFF377224FF0FA41CFF377224FF4C4C
      4CFF7C7C7CFFC4C4C4FFF4F4F4FF00000000AE7B6EFFD9AD9DFFD5AA9CFFD1A7
      9AFFCEA498FFCBA196FFC89F93FFC49C92FFC09990FFBC968EFFB9938DFF967B
      71FF7C6B62FFE3E0DEFFF6F5F4FFFDFDFDFF0000000000000000BB8875FFFCE4
      CFFFFCE2CCFFFBE0C9FFFBDEC6FFFBDCC3FFFBDABFFFFBD9BCFFFAD6B8FFFAD5
      B5FFFAD3B1FFEFBFA8FF736158FFBFB7B3FF2187BAFF66CCFFFF1F85B8FF99FF
      FFFF6ED4FFFF6ED4FFFF6ED4FFFF6ED4FFFF6ED4FFFF6ED4FFFF6ED4FFFF6ED4
      FFFF3AA0D3FF99FFFFFF006699FF6C6C6CFF6FA5BFFF9FCFE2FF79D9FFFF5BCB
      F5FF46BCE9FF006600FF006600FF006600FF006600FF1BB436FF0FA81CFF3772
      24FF4C4C4CFF7E7E7EFFC8C8C8FFF6F6F6FFAE7B6EFFEFE7DEFFFFEEDDFFFFEA
      D6FFFFE6CDFFFFE3C8FFFFDFBEFFFFDCB9FFFFD8B2FFFFD4A9FFFFD0A2FFD9AA
      A8FF6F5D54FFBAAEAAFFF0EEEDFFFBFAFAFF0000000000000000C28F79FFFCE7
      D4FFFCE4D1FFFCE3CEFFFCE1CAFFFBDFC7FFFBDCC4FFFBDBC0FFFADABCFFFBD7
      B9FFFBD5B6FFF0C1ABFF736158FFBFB7B3FF248ABDFF66CCFFFF268CBFFF99FF
      FFFF7AE0FFFF7AE0FFFF7AE0FFFF7AE0FFFF7AE0FFFF7AE0FFFF7AE0FFFF7AE0
      FFFF43A9DCFF99FFFFFF01679AFF6B6B6BFF3F94B9FF70B7D6FFACECFFFF7AE0
      FFFF7AE0FFFF006600FF60F993FF50E983FF40D973FF28C150FF1BB436FF0FA8
      1CFF377224FF626262FFAAAAAAFFECECECFFECE5DFFFC28F79FFFFF2E5FFFFEE
      DDFF6A9D58FFFFE6CDFFFFE3C8FFFFDFBEFFFFDCB9FFFFD8B2FFFFD4A9FFF7BF
      B0FF7D655CFF968780FFEBE7E6FFFAF9F9FF0000000000000000C8957CFFFCE8
      D8FFFCE6D5FFFCE5D2FFFCE3CEFFFBE1CBFFFBE0C8FFFBDEC4FFFADCC1FFFBD9
      BEFFFAD8BBFFF0C3AFFF736158FFBFB7B3FF278DC0FF66CCFFFF2C92C5FF99FF
      FFFF85EBFFFF85EBFFFF85EBFFFF85EBFFFF85EBFFFF85EBFFFF85EBFFFF85EB
      FFFF4DB3E6FF99FFFFFF03699CFF6B6B6BFF5AA0C3FF4EA8D2FFD9F9FFFF85EB
      FFFF85EBFFFF006600FF60F993FF50E983FF40D973FF33CC65FF28C150FF1BB4
      36FF0DA019FF166F16FFC2C2C2FFF5F5F5FFF7F3EEFFC8957CFFFEF5EBFFFFF2
      E5FF2D842BFF7FA86AFFFFE6CDFFFFE3C8FFFFDFBEFFFFDCB9FFFFD8B2FFFFCF
      AEFF997D76FF796860FFE3DFDDFFF6F5F5FF0000000000000000CF9C80FFFCEB
      DDFFFDEADAFFFCE7D6FFFCE6D3FFFCE4CFFFFCE2CCFFFBE0C9FFFBDEC6FFFBDC
      C2FFFADBBFFFF1C5B1FF736158FFBFB7B3FF298FC2FF66CCFFFF3298CBFF99FF
      FFFF91F7FFFF91F7FFFF91F7FFFF91F7FFFF91F7FFFF91F7FFFF91F7FFFF91F7
      FFFF56BCEFFF99FFFFFF056B9EFF6B6B6BFF5EABCCFF58B5E2FFAFD9E9FF8FF5
      FFFF8FF5FFFF006600FF006600FF006600FF006600FF3ED771FF33CC65FF1DAA
      3BFF13621FFF767C76FFD1D1D1FFFBFBFBFF00000000CF9C80FFF3EFEAFFFFF5
      ECFF2D842BFF2D842BFFB1C194FFFFE6CDFFFFE3C8FFFFDFBEFFFFDCB9FFFFD8
      B2FFDDA5A1FF6F5C53FFB9AEA9FFF1EFEDFF0000000000000000D5A283FFFDEE
      E0FFFDECDDFFFCEADBFFFCE8D7FFFCE6D3FFFCE4D1FFFBE2CDFFFBE1CAFFFBDF
      C6FFFBDDC3FFF2C8B5FF736158FFBFB7B3FF2C92C5FF6ED4FFFF3399CCFF99FF
      FFFF99FFFFFF99FFFFFF99FFFFFF99FFFFFF99FFFFFF99FFFFFF99FFFFFF99FF
      FFFF5FC5F8FF99FFFFFF076DA0FF6C6C6CFF5FADCEFF75B7D8FF66A9C6FFB9FF
      FFFF99FFFFFF99FFFFFF99FFFFFF99FFFFFF377224FF4BE47EFF22A53FFF3772
      24FF297E9DFF686868FFB8B8B8FFF2F2F2FF2D842BFF2D842BFF2D842BFF2D84
      2BFF2D842BFF1EB73CFF0D8212FFE9DFC4FFFFE6CDFFFFE3C8FFFFDFBEFFFFDC
      B9FFF7B9ACFF7F685EFF978881FFEBE8E7FF0000000000000000DCA987FFFEF0
      E5FFFDEEE1FFFDECDFFFFDEBDBFFFDE9D8FFFCE6D5FFFCE5D1FFFBE3CEFFFCE1
      CAFFFBDFC7FFF2C9B7FF736158FFBFB7B3FF2E94C7FF7AE0FFFF2C92C5FFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFF80E6FFFFFFFFFFFF0A70A3FF8B8B8BFF48A0C6FF7EBDD9FF51849BFFCAEC
      F5FFE3FFFFFFD9FFFFFFC6FFFFFFB9FFFFFF377224FF2DA344FF377224FFD6FF
      FFFF86CCDFFF3D5663FF949494FFE2E2E2FF339039FF55EF88FF47E17BFF39D3
      6CFF31CA63FF21BB44FF10A821FF248020FFFFEAD6FFFFE6CDFFFFE3C8FFFFDF
      BEFFFFD2B7FF9E857BFF796860FFE3DFDDFF0000000000000000DCA987FFFDF3
      EAFFFDF1E6FFFDEFE3FFFDEDDFFFFCEBDCFFFDE9D9FFFDE7D6FFFCE5D3FFFCE4
      CFFFFCE1CBFFF3CCBAFF736158FFBFB7B3FF3096C9FF85EBFFFF80E6FFFF2C92
      C5FF2C92C5FF2C92C5FF2C92C5FF2C92C5FF2C92C5FF278DC0FF2389BCFF1F85
      B8FF1B81B4FF1A80B3FF1A80B3FFDEDEDEFF4C9FC6FF8EC9D9FFB3ABA9FF9FA6
      99FF70A4AFFF70AABEFF80BCD2FFECFFFFFF377224FF377224FFB7F2FFFFF0FF
      FFFFE1F9FCFF30738FFF868686FFD9D9D9FF339039FF48D973FF3CCD67FF31C2
      5CFF2BBD57FF25BE4BFF12A525FF2D842BFFFFEEDDFFFFEAD6FFFFE6CDFFFFE3
      C8FFFFDFBEFFE1A29BFF705E54FFBBB0ABFF0000000000000000DCA987FFFDF5
      EDFFFEF3EAFFFDF2E7FFFDEFE4FFFDEDE1FFFDECDEFFFCEADAFFFCE8D7FFFCE6
      D3FFFCE4D0FFF3CDBDFF78675FFFC2B9B5FF3298CBFF91F7FFFF8EF4FFFF8EF4
      FFFF8EF4FFFF8EF4FFFF8EF4FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFF157BAEFF8B8B8BFFDDDDDDFFFEFEFEFF6CACCCFF99D2D9FFC7BAB3FFFFCF
      9FFFFFCF9EFFFFD1A3FFCFB999FF60A6C3FF377224FFAFD2E2FFB3E2F2FFFFFF
      FFFFFFFFFFFF70B3CFFFAFAFAFFFE5E5E5FF0000000000000000CF9C80FFC8D1
      BBFF2B8C34FF27BF4EFF268528FFFFF5ECFFFFF2E5FFFFEEDDFFFFEAD6FFFFE6
      CDFFFFE3C8FFF8B3A8FF826C61FF9B8C85FF0000000000000000DCA987FFFEF8
      F2FFFEF5EEFFFDF4ECFFFDF2E8FFFDF0E5FFFDEEE2FFFDECDEFFFDEADAFFFCE8
      D8FFFCE6D4FFF4C9BAFF887970FFCCC4C0FF3399CCFFFFFFFFFF99FFFFFF99FF
      FFFF99FFFFFF99FFFFFFFFFFFFFF248ABDFF2187BAFF1E84B7FF1C82B5FF1A80
      B3FF177DB0FFDEDEDEFFF6F6F6FF0000000073B8D6FFA1D7D9FFCBBFB7FFFFD2
      A6FFFFCF9FFFFFD4A8FFFFCC99FFFFD2A5FFE4B8A7FF609FACFF39A9C9FF2C6F
      8EFF5496B3FF72A9C2FFE9E9E9FFF8F8F8FF0000000000000000F2EEE7FFCF9C
      80FF32903BFF1E8628FFF7F9F4FFFFF8F1FFFFF5ECFFFFF2E5FFFFEEDDFFFFE4
      D3FFFFDEC9FFFFC4B6FFA2887EFF85746CFF0000000000000000DCA987FFFFFA
      F7FFFEF8F3FFFEF6F0FFFEF4ECFFFEF2E9FFFDF1E6FFFDEFE2FFFFD5CCFFFFD5
      CCFFF5B3AAFFB3887DFFA99D95FFDDD8D6FF000000003399CCFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFF298FC2FFC7C7C7FFF5F5F5FFFEFEFEFFFEFEFEFFFEFE
      FEFFFEFEFEFFFEFEFEFF00000000000000006AAECBFFBED1D6FFD0C3BAFFFFFF
      FFFFFFFEFDFFFFF7EFFFFFEBD7FFFAE3CCFFE5B5A7FF84A5ACFF5CB9D6FF89A2
      AFFFE5E5E5FFFCFCFCFF0000000000000000000000000000000000000000DCA9
      87FF2F812FFFDBE9DBFFFFFFFFFFFFFDFBFFFFF8F1FFFFF5ECFFF8E6D7FFDBA3
      83FFD69671FFD08E6CFFBF9E84FFC0B6B0FF0000000000000000DCA987FFFFFD
      FBFFFFFBF7FFFEF9F4FFFEF7F1FFFEF5EDFFFDF3EBFFFDF1E7FFF7A643FFF7A6
      43FFE09240FF96867CFFCDC3C0FFF0ECEAFF00000000000000003399CCFF3298
      CBFF3096C9FF2E94C7FFDEDEDEFFF5F5F5FF0000000000000000000000000000
      000000000000000000000000000000000000DEEAF1FF669CB2FFD5C8BDFFFFFF
      FFFFFFFFFFFFFFFEFDFFFFF9F4FFFAD098FFDD984AFF5F737BFF7DA3B6FFEEEE
      EEFFFBFBFBFF000000000000000000000000000000000000000000000000DCA9
      87FFF9F2EBFFFFFFFFFFFFFFFFFFFFFFFFFFFFFDFBFFFFF8F1FFFDF3E9FFDCA9
      87FFFFB34EFFE0A86CFFC7B8B0FFEDEAE9FF0000000000000000DCA987FFFFFF
      FFFFFFFEFBFFFFFBF8FFFEFAF5FFFEF8F1FFFEF6EEFFFDF3ECFFDCA987FFEAB3
      76FF8C7363FFB9AFA9FFE6E1DEFFF9F8F6FF000000000000000000000000FEFE
      FEFFFEFEFEFFFEFEFEFFFEFEFEFF000000000000000000000000000000000000
      00000000000000000000000000000000000000000000D6D6D6FFD9CCBFFFFDFD
      FDFFF9F9F9FFF9F9F9FFF8F7F6FFF9DEB3FF988068FFC1C1C1FFF3F3F3FFFEFE
      FEFF00000000000000000000000000000000000000000000000000000000FBF8
      F1FFDCA987FFFEFEFEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFDFBFFFFF8F1FFDCA9
      87FFE6BB93FFCCC1B9FFEEECEBFFF8F7F6FF0000000000000000DCA987FFDCA9
      87FFDCA987FFDCA987FFDCA987FFDCA987FFDEAB88FFD6A384FFDCA987FFF8EF
      EAFF000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000CCC5BFFFC7BA
      AEFFA79A8FFFC4B7AEFFA89B94FFA1988DFFD7D7D7FFF4F4F4FFFEFEFEFF0000
      0000000000000000000000000000000000000000000000000000000000000000
      0000DCA987FFDCA987FFDCA987FFDCA987FFDCA987FFDCA987FFDCA987FFDCA9
      87FFE5DFDAFFF2F1F0FFF9F8F8FFFDFDFDFF424D3E000000000000003E000000
      2800000040000000300000000100010000000000800100000000000000000000
      000000000000000000000000FFFFFF0000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000C000800000078000C000000000030000
      C000000000010000C000000000000000C000000000000000C000000000000000
      C000000000008000C000000000000000C000000000000000C000000000000000
      C00000000000C000C00000010000C000C00080030003E000C000C0FF0007E000
      C000E1FF800FE000C00FFFFFC01FF00000000000000000000000000000000000
      000000000000}
  end
end
