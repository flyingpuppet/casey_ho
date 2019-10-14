object Form_AXI_IDList: TForm_AXI_IDList
  Left = 248
  Top = 160
  BorderIcons = []
  BorderStyle = bsNone
  Caption = 'Form_AXI_IDList'
  ClientHeight = 344
  ClientWidth = 202
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object clb_axi_agents: TCheckListBox
    Left = 0
    Top = 0
    Width = 200
    Height = 321
    ItemHeight = 13
    Items.Strings = (
      'me_i_y_r'
      'me_p_y_r'
      'me_i2_y_r'
      'me_mv1_w '
      'me_mv1_r '
      'me_pi_v_w'
      'me_pi_v_r'
      'me_ppi_v_r'
      'mc_i_y_r(dp_y_r)'
      'mc_i_c_r(dp_cb_r)'
      'mc_p_y_r'
      'mc_p_c_r(dp_cr_r@444)'
      'ip_y_w'
      'ip_c_w(ip_cb_w@444)'
      'ip_qy_w(Q_pixel_y||ip_cr_w@444)'
      'ip_fdet_r'
      'ip_logo_w'
      'ip_logo_r'
      'logo_mask_w'
      'logo_mask_r'
      'vdp_r'
      'vdp_w'
      'all_r'
      'all_w')
    TabOrder = 0
  end
  object BitBtn1: TBitBtn
    Left = 0
    Top = 320
    Width = 65
    Height = 25
    TabOrder = 1
    OnClick = BitBtn1Click
    Kind = bkOK
  end
  object BitBtn2: TBitBtn
    Left = 136
    Top = 320
    Width = 65
    Height = 25
    TabOrder = 2
    Kind = bkCancel
  end
end
