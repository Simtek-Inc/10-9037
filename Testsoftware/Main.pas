unit Main;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ExtCtrls, ComCtrls, Menus, IniFiles, Math,
  DXClass, DIB, ExtDlgs, IdBaseComponent, IdComponent, IdUDPBase,
  ShellAPI, jpeg, CPDrv, fileCtrl, spin, Buttons, ImgList,
  ToolWin;




const


  lblAddressWWW      = 'www.simtekinc.com';
  fileCFG            = 'simtek.dcf';

  InstNum            = '9037';
  InstHead           = '10';
  InstRevLevel       = '-';


  lblTestSoftwareCap = ': '+InstHead+'-' + InstNum;
  lblTestSoftwareRev = ':   ' + InstRevLevel;
  lblWARNINGCaption  = 'CAUTION FOR USE IN' +#$0D#$0A+ 'FLIGHT SIMULATOR ONLY';

  InstRevInf         = InstHead + '-' + InstNum+' Test Software Rev ' + InstRevLevel;
  InstSec            = '10' + InstNum;

  icTXQue            = 512;
  icRXQue            = 1024;
  dsf                = 'Courier,8,clWindowText,clWindow';

  GENSec             = 'general';
  InstSecK01         = 'edtIPAddress';
  InstSecK02         = 'edtClientPort';
  InstSecK03         = 'edtAddress';

  GenSecK01          = 'TxWinLimit';
  GenSecK02          = 'RxWinLimit';
  GenSecK03          = 'cpdDATABITS';
  GenSecK04          = 'cpdPARITY';
  GenSecK05          = 'cpdSTOPBITS';
  GenSecK12          = 'memolog';
  GenSecK13          = 'memotrx';
  GenSecK14          = 'memordx';
  GenSecK15          = 'memoraw';
// Host Command Setn to the Instrument
  TSCapHeader        = ' Transmit speed = ';

  lenDefault         = 6;

  C0Command          = 'Reset';
  C0Request          = $F0; // Reset
  C0Requestlength    = 2;
  C0CapHeader        = C0Command + ' Transmit speed = ';
  C0Response         = C0Request;
  C0Responselength   = 0;

  C1Command          = 'Command';
  C1Request          = $F5; // Command
  C1Requestlength    = 4;
  C1CapHeader        = C1Command + ' Transmit speed = ';
  C1DeviceValDefault = ': 7?-???? Rev ?';
  C1Response         = C1Request;
  C1Responselength   = 0;

  C2Command          = 'Firmware';
  C2Request          = $FE; // firmware
  C2Requestlength    = 2;
  C2CapHeader        = C2Command + ' Transmit speed = ';
  C2Response         = C2Request;
  C2Responselength   = 6;

type
 Tx = record
   s    : string;                               //
   ai   : byte;                                 // average update rate index
   ar   : array[0..255] of double;              // average update rate
   us   : double;                               // update speed
   ui   : byte;                                 // update index
   uc   : integer;                              // update rate count
end;


type
    TMainForm = class(TForm)
    MainMenu1: TMainMenu;
    mm01: TMenuItem;
    Exit1: TMenuItem;
    Port1: TMenuItem;
    StatusBar: TStatusBar;
    mm02: TMenuItem;
    mm02s01: TMenuItem;
    mm02s02: TMenuItem;
    mm06: TMenuItem;
    mm05: TMenuItem;
    mm04: TMenuItem;
    PageControl1: TPageControl;
    TabSheet1: TTabSheet;
    lblScrollRate: TLabel;
    lblTestSoftwarePNValue: TLabel;
    lblWARNING: TLabel;
    lblTestSoftwarePNTile: TLabel;
    lblTestSoftwareRevValue: TLabel;
    lblTestSoftwareRevTile: TLabel;
    imgSimtekLogo: TImage;
    lblFirmwareTitle1: TLabel;
    lblFirmwareValue1: TLabel;
    pnlDividerBar05: TPanel;
    pnlDividerBar03: TPanel;
    pnlDividerBar01: TPanel;
    pnlDividerBar02: TPanel;
    pnlDividerBar04: TPanel;
    tkbScrollRate: TTrackBar;
    TabSheet4: TTabSheet;
    lblResponseRequestsTitle1: TLabel;
    lblResponseRequestsTitle2: TLabel;
    lblRecievedTimeout: TLabel;
    lblC1TransmitRate: TLabel;
    lblC2TransmitRate: TLabel;
    lblTransmitRate: TLabel;
    lblRequestsSent: TLabel;
    lblResponseRecieved: TLabel;
    cbxResponse: TCheckBox;
    tkbRecieveTimeOut: TTrackBar;
    tkbC1UpdateRate: TTrackBar;
    tkbC2UpdateRate: TTrackBar;
    tbUpdateRate: TTrackBar;
    cbxGraphicsEnable: TCheckBox;
    cbxTRXWindowEnable: TCheckBox;
    cbxRDXWindowEnable: TCheckBox;
    DXTimer1: TDXTimer;
    mm03: TMenuItem;
    mm03s01: TMenuItem;
    mm03s02: TMenuItem;
    mm03s03: TMenuItem;
    mm03s04: TMenuItem;
    mm03s05: TMenuItem;
    mm03s05s01: TMenuItem;
    mm03s05s02: TMenuItem;
    mm03s05s03: TMenuItem;
    N2: TMenuItem;
    N1: TMenuItem;
    N3: TMenuItem;
    mm02s03: TMenuItem;
    mm08: TMenuItem;
    lblTransmitted: TLabel;
    lblReceived: TLabel;
    PopupMenu1: TPopupMenu;
    Cut1: TMenuItem;
    Copy1: TMenuItem;
    Paste1: TMenuItem;
    Delete1: TMenuItem;
    MenuItem1: TMenuItem;
    Selectall1: TMenuItem;
    MenuItem2: TMenuItem;
    pmClearAll: TMenuItem;
    N4: TMenuItem;
    Print1: TMenuItem;
    lblAvailablePortsTitle: TLabel;
    lblBaudRateTitle: TLabel;
    cbBaudRate: TComboBox;
    lblBaudRateColon: TLabel;
    lblAvailablePortsColon: TLabel;
    cbValidPorts: TComboBox;
    MemoTx: TRichEdit;
    CPDrv: TCommPortDriver;
    MemoRx: TRichEdit;
    cbfilterGarbage: TCheckBox;
    panel1: TPanel;
    lblAddressTitle: TLabel;
    Label2: TLabel;
    cbAddress: TComboBox;
    mm03s05s04: TMenuItem;
    Panel3: TPanel;
    tkb_DialSlider: TTrackBar;
    edt_Dial: TEdit;
    lbl_deg: TLabel;
    lbl_0: TLabel;
    lbl_10: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    lbl_DacValue: TLabel;
    Label6: TLabel;
    lbl_9: TLabel;
    lbl_8: TLabel;
    lbl_7: TLabel;
    lbl_6: TLabel;
    lbl_5: TLabel;
    lbl_4: TLabel;
    lbl_3: TLabel;
    lbl_2: TLabel;
    lbl_1: TLabel;

    procedure Exit1Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);

    procedure mm02s01Click(Sender: TObject);
    procedure mm02s02Click(Sender: TObject);

    procedure mm05Click(Sender: TObject);
    procedure tbUpdateRateChange(Sender: TObject);
    procedure tkbC1UpdateRateChange(Sender: TObject);
    procedure tkbC2UpdateRateChange(Sender: TObject);
    procedure cbxResponseClick(Sender: TObject);
    procedure tkbRecieveTimeOutChange(Sender: TObject);
    procedure imgSimtekLogoClick(Sender: TObject);
    procedure tkbScrollRateChange(Sender: TObject);
    //procedure paintGUI;
    procedure decodeRecievedData(s : string);
    procedure decodeSerial(var sp1, sp2 : string);
    function  encodeCommandData(CommandByte : byte) : string;
    function  calculateRate(ct : double;g : Tx;rc : boolean;l : TObject;t : TObject;s : string):Tx;

    procedure cpOutputData(s : string; rc : boolean);
    procedure wrMemoWindow(show,memo,lbl :TObject; Limit,Place : integer;head,cap,s : string);
    procedure lblFirmwareTitle2Click(Sender: TObject);

    procedure DXTimer1Timer(Sender: TObject; LagCount: Integer);
    function  buildMainCaption : string;

    procedure responseReset;

    //serial interface
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    procedure parseFont(memo : TRichEdit;sf,section,key : string;sini : TIniFile);
    procedure cpSetComPort();
    function  cpIntToBaudRate(rate: string): TBaudRate; {Reads data from the serial port and posts a message}
    function  cpIntToBaud(baud : integer) : string;
    function  cpParityToInt(parity : string):integer;
    function  cpIntToParity(parity: TParity): string;
    function  cpIntToStopBits(stopbits : TStopBits):string;
    function  cpStopBitsToInt(stopbits : string):integer;
    function cleanRxBuffer(len : integer) : string;
    procedure responseFirmware(s : string); // only have one RS
    procedure responseStatus(ptrCK: pbyte);
    procedure parseTx(s : String);
    procedure cpGetData(instr : string) ;
    //----------------------------------------------------------------------------------------------------------------------

    procedure mm03s01Click(Sender: TObject);
    procedure mm02s03Click(Sender: TObject);
    procedure mm03s03Click(Sender: TObject);
    procedure mm03s05s01Click(Sender: TObject);
    procedure MemoTxChange(Sender: TObject);
    procedure memoTxKeyPress(Sender: TObject; var Key: Char);
    procedure MemoRxChange(Sender: TObject);
    procedure MemoRxKeyPress(Sender: TObject; var Key: Char);


    //$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

    //$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

    procedure saveSettings;
    procedure cbBaudRateChange(Sender: TObject);
    procedure cbValidPortsChange(Sender: TObject);
    procedure cpDRVReceiveData(Sender: TObject; DataPtr: Pointer;
      DataSize: Cardinal);
    procedure cbAddressChange(Sender: TObject);
    procedure mm06Click(Sender: TObject);
    procedure mm04Click(Sender: TObject);
    procedure mm08Click(Sender: TObject);
    procedure tkb_DialSliderChange(Sender: TObject);
    procedure edt_DialKeyPress(Sender: TObject; var Key: Char);
    procedure edt_DialClick(Sender: TObject);
    function convertDegrees(num : integer) : string;
    procedure scrollEverything();
    procedure edt_DialKeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure lbl_0Click(Sender: TObject);
    procedure lbl_1Click(Sender: TObject);
    procedure lbl_2Click(Sender: TObject);
    procedure lbl_3Click(Sender: TObject);
    procedure lbl_4Click(Sender: TObject);
    procedure lbl_5Click(Sender: TObject);
    procedure lbl_6Click(Sender: TObject);
    procedure lbl_7Click(Sender: TObject);
    procedure lbl_8Click(Sender: TObject);
    procedure lbl_9Click(Sender: TObject);
    procedure lbl_10Click(Sender: TObject);

   private
    { Private declarations }

  public
    { Public declarations }

  end;

type
  TComRecord = Record
    Port  : ShortInt;
    Baud  : ShortInt;
    Parity: ShortInt;
    DataBits : ShortInt;
    StopBits : ShortInt;
    HandShak : ShortInt;
end;

var

  MainForm   : TMainForm;
  hWind      : HWND;
  {------------- Variables for serial Communications -----------------------------------------}
  gPort                     : String;                // open port name
  gBaud                     : String;                // port baud rate
  gAddress                  : byte;
  gDataBits                 : String;                // port data bits
  gStopBits                 : String;                // port stop bits
  gParity                   : String;                // port parity setting
  LightTXOnTime             : integer = 1;           // define counter to keep activity TX light on
  LightRXOnTime             : integer = 1;           // define counter to keep activity RX light on
  DisplayPortDialog         : integer = 0;           //
  TxWinLimit                : integer = 250;         //
  RxWinLimit                : integer = 250;         //
  RxPlace                   : integer = 0;           //
  TxPlace                   : integer = 0;           //
  ComStat    : TComStat;  { Com Status Structure }
  hComm      : HWND = INVALID_HANDLE_VALUE;
  PortInfo   : TComRecord;
  DCB        : TDCB;
  TpCommProp : TCommProp;
  TimeOuts   : TCommTimeouts;
  zsRXBuff   : array[0..2047] of char;
  bBindex    : byte;
  bEindex    : byte;
  lzsBuffer  : array[0..255] of char;
  //  MY VARIABLES FOR PROGRAM  DME PANEL
  Txc,Rxc : TColor;
  VersionInfo : TOSVERSIONINFO;

  PanelMap   : TBitMap; // holds the bitmap for the instrument face
  OSBitMap1  : TBitMap; // off-screen bitmap you do your drawing on
  OSBitMap2  : TBitMap; // off-screen bitmap you do your drawing on

// variables for serial message shortfalls
  gSerialBuffer             : string  = '';          //
  gSerialBufferSMsg         : string  = '';          //
  gByteCount                : word    = 0;           //
  gWholeMsg                 : integer = lenDefault;  //

  TXCount                  : byte    = 1; {define and initilize Counter}
  RXCount                  : byte    = 1; {define and initilize Counter}
  sWidth                   : integer = 1024;

  fScrollReq               : boolean = False;
  dScrollValue             : byte = 0;
  ScrollCount              : integer = 0;

// Device Output control variables
  fImageRedraw             : boolean;
  IndicatorData            : array[0..C2Requestlength] of byte;

// Host to Instrument request Action Flags
  fC0Request               : boolean  = False; // reset
  fC1Request               : boolean  = False; // Command
  fC2Request               : boolean  = False; // firmware rev

  // storage
  C0RequestData            : array[0..C0Requestlength-1] of byte; // reset
  C1RequestData            : array[0..C1Requestlength-1] of byte; // command
  C2RequestData            : array[0..C2Requestlength-1] of byte; // Firmware

// Debug Variables
  NumberOfRequests         : cardinal = 0;
  UserImageSelected        : boolean  = True;
  NumberOfResponse         : cardinal = 0;

  //integer to hold count down for txshape blink on transmission
  tx_integer, rx_integer : integer;

  statusFlg : boolean;
  oldSlider : integer = 0;
  ltime                    : TDateTime;                // current time

  gRate                    : Tx;
  gRateC1                  : Tx;
  gRateC2                  : Tx; // DisplayRequest     = $F2;
  gRateC3                  : Tx; // DimmingRequest     = $F3;
  gRateC4                  : Tx; // FirmwareRequest    = $F4;
  gRateC5                  : Tx; // FirmwareRequest    = $F4;
  gRateC6                  : Tx; // FirmwareRequest    = $F4;
  BurstFileName            : string = 'BurstFile.txt';
  BurstFileContents        : TStringlist = nil;
  //bit to reset procedures

 scrollDial : integer;
 scrollDir  : boolean;

implementation

//uses UAbout, PortDlg;
{$R *.DFM}
//
procedure TMainForm.Exit1Click(Sender: TObject);
begin
Close;
end;

procedure TMainForm.mm02s01Click(Sender: TObject);
begin
MemoRx.Clear;
end;

procedure TMainForm.mm02s02Click(Sender: TObject);
begin
MemoTx.Clear;
end;



procedure TMainForm.mm02s03Click(Sender: TObject);
begin
  NumberOfRequests                := 0;
  NumberOfResponse                := 0;
end;


procedure TMainForm.tbUpdateRateChange(Sender: TObject);
begin
 if tbUpdateRate.Position = 0 then DXTimer1.Interval := 0 else DXTimer1.Interval := 1;
 if tkbScrollRate.Position < tbUpdateRate.Position then
   tkbScrollRate.Position := tbUpdateRate.Position;
end;

procedure TMainForm.mm05Click(sender: TObject);
begin
  if fScrollReq = false then fScrollReq := true else fScrollReq := false;
end;

procedure TMainForm.mm06Click(Sender: TObject);
begin
        fC0Request := true;
        responseReset;
end;

procedure TMainForm.mm08Click(Sender: TObject);
begin
  fC2Request := true;
end;

procedure TMainForm.imgSimtekLogoClick(Sender: TObject);
var url : string;
begin
  url := lblAddressWWW;
  ShellExecute(self.WindowHandle,'open',PChar(url),nil,nil, SW_SHOWNORMAL);
end;


procedure TMainForm.lbl_6Click(Sender: TObject);
begin
tkb_DialSlider.Position := 2457;
end;

procedure TMainForm.lbl_5Click(Sender: TObject);
begin
tkb_DialSlider.Position := 2048;
end;

procedure TMainForm.lbl_4Click(Sender: TObject);
begin
tkb_DialSlider.Position := 1638;
end;

procedure TMainForm.lbl_3Click(Sender: TObject);
begin
tkb_DialSlider.Position := 1229;
end;

procedure TMainForm.lbl_2Click(Sender: TObject);
begin
tkb_DialSlider.Position := 819;
end;

procedure TMainForm.lbl_1Click(Sender: TObject);
begin
tkb_DialSlider.Position := 410;
end;

procedure TMainForm.lbl_10Click(Sender: TObject);
begin
tkb_DialSlider.Position := 4095;
end;

procedure TMainForm.lbl_9Click(Sender: TObject);
begin
tkb_DialSlider.Position := 3686;
end;

procedure TMainForm.lbl_8Click(Sender: TObject);
begin
tkb_DialSlider.Position := 3276;
end;

procedure TMainForm.lbl_7Click(Sender: TObject);
begin
tkb_DialSlider.Position := 2867;
end;

procedure TMainForm.lbl_0Click(Sender: TObject);
begin
tkb_DialSlider.Position := 0;
end;

procedure TMainForm.lblFirmwareTitle2Click(Sender: TObject);
begin
  lblFirmwareValue1.Caption := C1DeviceValDefault;
end;



procedure TMainForm.FormCreate(Sender: TObject);
var i, tmp            : integer;
    PaintBoxRect : TRect ;
    OSBitRect    : TRect ;
    SIni    : TIniFile;
begin


  memoTx.Clear;                                                                               // clear out the transmit window.
  memoRx.Clear;                                                                               // clear out the receive window.

  SIni := nil;
  SIni := TIniFile.Create(ChangeFileExt(Application.ExeName,'.ini'));
  try
    begin
          With SIni do
      begin
        TxWinLimit                :=                ReadInteger(GENSec,  GenSecK01,  250);    //
        RxWinLimit                :=                ReadInteger(GENSec,  GenSecK02,  250);    //
        // load the com port setting if they are stored else load the defaults
        gPort                     :=                ReadString(InstSec, InstSecK01, 'COM3');  //
        gBaud                     :=                ReadString(InstSec, InstSecK02, '9600');  //
        gAddress                  :=       StrtoInt(ReadString(InstSec, InstSecK03,    '1'));
        gDataBits                 :=                ReadString(GENSec,  GenSecK03,  '3');     //
        gStopBits                 :=                ReadString(GENSec,  GenSecK04,  '1');     //
        gParity                   :=                'odd';//   ReadString(InstSec, GenSecK05,  'none');  //
      end;
    end;
  finally
    Sini.Free;
  end;
//  SIni := TIniFile.Create('C:\Simtek.Ini');
//    With SIni do
//      begin
//        TxWinLimit                :=                ReadInteger(GENSec,  GenSecK01,  250);    //
//        RxWinLimit                :=                ReadInteger(GENSec,  GenSecK02,  250);    //
//        // load the com port setting if they are stored else load the defaults
//        gPort                     :=                ReadString(InstSec, InstSecK01, 'COM3');  //
//        gBaud                     :=                ReadString(InstSec, InstSecK02, '9600');  //
//        gAddress                  :=       StrtoInt(ReadString(InstSec, InstSecK03,    '1'));
//        gDataBits                 :=                ReadString(GENSec,  GenSecK03,  '3');     //
//        gStopBits                 :=                ReadString(GENSec,  GenSecK04,  '1');     //
//        gParity                   :=                'odd';//   ReadString(InstSec, GenSecK05,  'none');  //
//      end;
//    Sini.Free;

    TxPlace                         := Length(IntToStr(TxWinLimit));                            // get the number of possible lines in the window
    RxPlace                         := Length(IntToStr(RxWinLimit));                            // get the number of possible lines in the window

    cbValidPorts.Text := gPort;
    cbBaudRate.Text   := gBaud;
    cbAddress.Text    := InttoStr(gAddress);

    responseReset;
    fImageRedraw                  := true;
    DXTimer1.Enabled              := true;

end;

procedure TMainForm.responseReset;
begin
    memoTx.Clear;                              // Blank the dataout and datain
    memoRx.Clear;                              // Blank the dataout and datain

    mm06.Caption                     := '&'+C0Command;
    mm04.Caption                     := C1Command;
    mm08.Caption                     := C2Command;

    mm03s05s01.Caption               := '&'+C1Command;
    mm03s05s02.Caption               := '&'+C2Command;

    tkb_DialSlider.Position := 0;
    lblFirmwareValue1.Caption        := C1DeviceValDefault;

    lblScrollRate.caption   := 'Scroll Rate Value: ' + InttoStr(tkbScrollRate.Position);

    MainForm.Caption                 := buildMainCaption;       //
    CPsetComPort;
    lblTransmitRate.Caption          := TSCapHeader + '0.00Hz';
    lblC1TransmitRate.Caption        := C1CapHeader + '0.00Hz';
    lblC2TransmitRate.Caption        := C2CapHeader + '0.00Hz';

    lblTestSoftwarePNValue.Caption   := lblTestSoftwareCap;
    lblTestSoftwareRevValue.Caption  := lblTestSoftwareRev;
    lblWARNING.Caption               := lblWARNINGCaption;

    ScrollDial := 0;
    ScrollDir := True;

end;

procedure TMainForm.responseFirmware(s : string);
var
  si    : string;
  b1,b2 : byte;
begin
    inc(NumberOfResponse);
    b2 := Ord(s[3]);
    b1 := ((b2 shr 4) and $0F) or $30;
    b2 := (b2 and $0F) or $30;
    si := ': ' + chr(b1) + chr(b2) + '-';
    b2 := Ord(s[4]);
    b1 := ((b2 shr 4) and $0F) or $30;
    b2 := (b2 and $0F) or $30;
    si := si + chr(b1) + chr(b2);
    b2 := Ord(s[5]);
    b1 := ((b2 shr 4) and $0F) or $30;
    b2 := (b2 and $0F) or $30;
    si := si + chr(b1) + chr(b2) + ' rev ';
    si := si + s[6];
    lblFirmwareValue1.Caption := si;
end;

procedure TMainForm.responseStatus(ptrCK: pbyte);
var
  tmp : byte;
begin

end;

procedure TMainForm.tkbC1UpdateRateChange(Sender: TObject);
begin
    if not(mm03s05.Checked and mm03s02.Checked and mm03s05s02.Checked) then
  begin
    lblC1TransmitRate.Caption := C1CapHeader + IntToStr(tkbC1UpdateRate.Position);
  end;

  //fImageRedraw := True;
end;

procedure TMainForm.tkbC2UpdateRateChange(Sender: TObject);
begin
    if not(mm03s05.Checked and mm03s02.Checked and mm03s05s02.Checked) then
  begin
    lblC2TransmitRate.Caption := C2CapHeader + IntToStr(tkbC2UpdateRate.Position);
  end;

  //fImageRedraw := True;
end;

procedure TMainForm.edt_DialClick(Sender: TObject);
begin
  TEdit(Sender).Selectall;
end;

procedure TMainForm.edt_DialKeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
//  var tmp : Extended;
//  const FeetPerStep = (50000/4095);
begin
  if Key = VK_RETURN then
  begin
    try
//      if StrToFloat(edt_Dial.text) > 4095 then
//        edt_Dial.text := FloatToStrF(50,fffixed,18,1);
//      if StrToFloat(edt_Dial.text) < 0 then
//        edt_Dial.text := FloatToStrF(0,fffixed,18,1);
      if StrToInt(edt_Dial.text) > 4095 then
        edt_Dial.text := IntToStr(4095);
      if StrToInt(edt_Dial.text) < 0 then
        edt_Dial.text := IntToStr(0);
    except
//      edt_Dial.text := FloatToStrF(0,fffixed,18,1);
      edt_Dial.text := IntToStr(0);
    end;{try except}
//    tkb_DialSlider.Position := round(StrToFloat(edt_Dial.Text));
//    tmp := (StrToFloat(edt_Dial.Text) * 1000);
//    tkb_DialSlider.Position := round(tmp / FeetPerStep);
    tkb_DialSlider.Position := StrToInt(edt_Dial.text);
    edt_Dial.SelectAll;
  end;
end;

procedure TMainForm.edt_DialKeyPress(Sender: TObject; var Key: Char);
begin
  case key of
    '0'..'9':;  // numbers
    '.':;       // decimal point
    #8:;         // backspace
    #13:;         // Enter
  else
  begin
    MessageDlg('Numbers only Please.  Valid characters are'+ #13 + #10 +
                '0 thru 9, Backspace, Enter and Delete.',mtInformation,
                [mbok],0);
    Key := #0;
  end;
  end;//case
//        statusFlg := True;
//        tkb_DialSlider.Position := StrtoInt(edt_Dial.Text);
//        ActiveControl := panel1;
//      end//case #13
//   else Key := #00;
//   end;
end;

function TMainForm.convertDegrees(num : integer) : string;
var PP : extended;
const FPS = 50000/4095;
begin
  PP := num * FPS / 1000;

//  else
Result := FloatToStrF(PP,ffFixed,5,3);

end;

function TMainForm.encodeCommandData(CommandByte: byte): string; //preps messages to be send to the instrument
var
   s          : string;
   tmp        : integer;
   cs         : byte;
   I          : integer;

   DPtr    : pbyte;
begin
  s := '';
  case CommandByte of

    C0Request  : begin               // reset
      s        := s + chr($F0);
      s        := s + chr(gAddress);
      inc(NumberOfRequests);
      end;
    C1Request  : begin               // Status
      s        := s + chr($F5);
      s        := s + chr(gAddress);
      s        := s + chr(tkb_DialSlider.Position and $3F);
      s        := s + chr((tkb_DialSlider.Position and $FC0) shr 6);
      inc(NumberOfRequests);
      end;
    C2Request  : begin                // Firmware
      s        := s + chr($FE);
      s        := s + chr(gAddress);
      inc(NumberOfRequests);
      end;
    else begin
      s   := chr(CommandByte);
    end;
  end;
  TXCount := 30;
  Result  := s;
end;

procedure TMainForm.MemoRxKeyPress(Sender: TObject; var Key: Char);
var UserrecieveString,CharacterCreationString,StringToRecieve : string;
    CharacterPointer,CharacterToRecieve,Stringlength,BadCharPos : byte;
begin
  case Key of
    '0'..'9':;
    'A'..'F':;
    'a'..'f':;
    #8 :;
    #13:begin
        UserrecieveString := memoRx.Lines.Strings[memoRx.Lines.Count-1];
        memoRx.Lines.Delete(memoRx.Lines.Count-1);
        BadCharPos := pos('>',UserrecieveString);
        if BadCharPos <> 0 then
          begin
          memoRx.Lines.Add(UserrecieveString);
          Delete(UserrecieveString,1,BadCharPos+1);
          end;
        While pos(' ',UserrecieveString) <> 0 do
          begin
          BadCharPos := pos(' ',UserrecieveString);
          Delete(UserrecieveString,BadCharPos,1);
          end;//while
        Stringlength := length(UserrecieveString);
        CharacterPointer := 1;
        StringToRecieve := '';
        While CharacterPointer <= Stringlength do
          begin
          CharacterCreationString := '$' + UserrecieveString[CharacterPointer] + UserrecieveString[CharacterPointer+1];
          CharacterToRecieve := StrToInt(CharacterCreationString);
          StringToRecieve := StringToRecieve + Chr(CharacterToRecieve);
          CharacterPointer := CharacterPointer + 2;
          end;
        if StringToRecieve <> '' then decodeRecievedData(StringToRecieve);
        Key := #00;
        end;
    else Key := #00;
  end;//case
end;


procedure TMainForm.MemoRxChange(Sender: TObject);
begin
  lblReceived.Caption := 'Lines Received : ' + IntToStr(memoRx.lines.count);
end;


procedure TMainForm.cbAddressChange(Sender: TObject);
begin
  gAddress :=cbAddress.ItemIndex;
  cpSetcomPort;
end;

procedure TMainForm.cbBaudRateChange(Sender: TObject);
begin
  gBaud := cpIntToBaud(cbBaudRate.ItemIndex);
  cpSetComPort;
end;

procedure TMainForm.cbValidPortsChange(Sender: TObject);
begin
  gPort := cbValidPorts.Text;
  UpperCase(gPort);
  cpSetComPort;
end;

procedure TMainForm.cbxResponseClick(Sender: TObject);
begin
  lblResponseRequestsTitle1.Visible := cbxResponse.Checked;
  lblRequestsSent.Visible           := cbxResponse.Checked;
  lblResponseRequestsTitle2.Visible := cbxResponse.Checked;
  lblResponseRecieved.Visible       := cbxResponse.Checked;
  lblRecievedTimeout.Visible        := cbxResponse.Checked;
  tkbRecieveTimeOut.Visible         := cbxResponse.Checked;
  N1.Visible                        := cbxResponse.Checked;
  mm02s03.Visible                   := cbxResponse.Checked;
  NumberOfRequests                  :=   0;
  NumberOfResponse                  :=   0;
end;



function  TMainForm.cleanRxBuffer(len : integer) : string;
var x : integer;
begin
//    Result := mem2str(gSerialBuffer,len);
  x        := 1;
  while(x <= len)do
  begin
    Result := Result + IntToHex(ord(gSerialBuffer[x]),2) + ' ';
    inc(x);
  end;
  delete(gSerialBuffer,1,len);
  gByteCount := length(gSerialBuffer);
  gWholeMsg  := lenDefault;
end;

// procedure  TMainForm.DXTimer1Timer(Sender: TObject; LagCount: Integer);
// 10/30/20 rev A sr.
// processing received data was based on receiving a minimum amount of data
//     if (gByteCount >= gWholeMsg) then process decode data.
//     when more data received  then proceede to decode message...
//     decodeSerial rev -  would not weed out any junk data and would hang.
//  changed if to ((gByteCount > 0) and (gSerialBufferSMsg <> ''))
//  decodeSerial now gets executed any time new data is received.
procedure TMainForm.DXTimer1Timer(Sender: TObject; LagCount: Integer);
var//  rxtimeout : integer;                 // timeout time for attempt to read receive buffer
     wdlist    : array[0..10] of string;  //
     wrstr     : string;                  // string to write to transmit buffer
     li        : integer;                 // line index
     counter   : integer;                 //
     ratecalc  : boolean;                 //
     ctime     : double;
begin
//  rxtimeout                   := tkbRecieveTimeOut.Position;
  wrstr                       := '';
  lblRequestsSent.Caption     := ': ' + IntToStr(NumberOfRequests);
  lblResponseRecieved.Caption := ': ' + IntToStr(NumberOfResponse);

    if ((gByteCount > 0) and (gSerialBufferSMsg <> '')) then
    begin
      decodeSerial(gSerialBuffer,gSerialBufferSMsg); // if there is junk data it gets weeded out
    end;//if ((gByteCount > 0) and (gSerialBufferSMsg <> ''))

  if fScrollReq then                             //scroll function
    begin
    if ScrollCount > tkbScrollRate.Position then
      begin
         scrollEverything();
         ScrollCount := 0;
      end;
      inc(ScrollCount);
    end;

  wrstr           := '';
  mm03s05.Checked := mm03s05s01.Checked
                  or mm03s05s02.Checked
                  or mm03s05s03.Checked
                  or mm03s05s04.Checked;
  inc(gRate.uc);

  if gRateC1.uc >= (tkbC1UpdateRate.Position) then
    begin
    if mm03s05.Checked and mm03s02.Checked then
      begin
      if mm03s05s01.Checked then fC1Request := True;
      end;
    gRateC1.uc := 0;
    end; //if gRateC1.uc >= (tkbC1UpdateRate.Position)then
  if gRateC2.uc >= (tkbC2UpdateRate.Position) then
    begin
    if mm03s05.Checked and mm03s02.Checked then
      begin      if mm03s05s02.Checked then fC2Request := True;   end;
    gRateC2.uc := 0;
    end; //if gRateC2.uc >= (tkbC2UpdateRate.Position)then
    
  ctime           := Now;
  li              := 0;

  if fC0Request then
    begin
    wrstr         := wrstr + encodeCommandData(C0Request);
    if mm03s04.Checked then
      begin
      inc(li);
      wdlist[li]  := wrstr;
      wrstr       := '';
      end;// mm03s04.Checked
    fC0Request    := False;
    end;// if fC0Request

  if fC1Request then
    begin
    wrstr         := wrstr + encodeCommandData(C1Request);
    if mm03s04.Checked then
      begin
      inc(li);
      wdlist[li]  := wrstr;
      wrstr       := '';
      end;// mm03s04.Checked
    gRateC1 := calculateRate(ctime, gRateC1, True, lblC1TransmitRate, tkbC1UpdateRate, C1CapHeader);
    fC1Request    := False;
    end;// if fC1Request

  if fC2Request then
    begin
    wrstr         := wrstr + encodeCommandData(C2Request);
    if mm03s04.Checked then
      begin
      inc(li);
      wdlist[li]  := wrstr;
      wrstr       := '';
      end;// mm03s04.Checked
    gRateC2 := calculateRate(ctime, gRateC2, True, lblC2TransmitRate, tkbC2UpdateRate, C2CapHeader);
    fC2Request    := False;
    end;// if fC2Request

  if mm03s03.Checked and (wrstr <> '') then
    begin
    inc(li);
    wdlist[li]    := wrstr;
    wrstr         := '';
    end;//if mm03s01.Checked
//
  if gRate.uc >= (tbUpdateRate.Position) then
    begin
    if mm03s02.Checked then gRate := calculateRate(ctime,    gRate, True, lblTransmitRate, tbUpdateRate, TSCapHeader)
    else                    gRate := calculateRate(gRate.uc, gRate, True, lblTransmitRate, tbUpdateRate, TSCapHeader);

    //if li <> 0 then
//      begin
      for counter  := 1 to li do
        begin
        wrstr           := wdlist[counter];
        wdlist[counter] := '';
        if counter       = li then ratecalc := True else  ratecalc := False;
        cpOutputData(wrstr, ratecalc);
        end;//for counter := 1 to li do
//      end;//if li <> 0 then
    gRate.uc := 0;
    inc(gRateC1.uc);
    inc(gRateC2.uc);
    inc(gRateC3.uc);
    inc(gRateC4.uc);
//    inc(gRateC5.uc);
//    inc(gRateC6.uc);
    end;//if gRate.uc >= (tbUpdateRate.Position) then

//  if (fImageRedraw and cbxGraphicsEnable.Checked) then
//    begin
//    paintGUI;
//    end;

end;

// procedure  TMainForm.decodeSerial(var sp1, sp2 : string);
// 10/30/20 rev A sr.
// if garbage data was at beginning of data stream....routine would lock up.
// reformatted "if thens" to "case" statement to make more concise.
procedure  TMainForm.decodeSerial(var sp1, sp2 : string);
var     // sp1 = gSerialBuffer    sp2 = gSerialBufferSMsg
  SMsg       : string;
//  s1         : string;       // FF0000531100000000000000000000080000
  tmp1 : byte;
  status : byte;
  //i          : integer;
begin
  sp1          := sp1 + sp2;   // add message to the buffer
  sp2          := '';         // clean out the message
  gByteCount  := length(sp1);  //set byte count to the length of the buffer
  SMsg := '';
//  status := 0;
  while(gByteCount > 0) do   // whole message is the minimum sized message I should recieve
  begin
    status := 0;
    tmp1 := Ord(sp1[1]);
    case tmp1 of
      $FE : begin
        gWholeMsg  :=  C2Responselength;
        status := 1;
        end;
//      $F1 : begin
//        gWholeMsg  :=  C1Responselength;
//        status := 1;
//        end;
      else begin
        SMsg := SMsg + sp1[1];
        cleanRxBuffer(1);  // clean out the junk
        end;
    end;

    if ((status = 1) and (gByteCount >= gWholeMsg)) then // are we good to process a message
    begin
      if ((cbfilterGarbage.Checked = false) and (SMsg <> '')) then // do we want to see any junk data
      begin                                                   //
        wrMemoWindow(cbxRDXWindowEnable,memoRx,lblReceived,RxWinLimit,RxPlace,'RX ','Lines Received : ',SMsg);
        SMsg := '';
      end;
      decodeRecievedData(copy(sp1,1,gWholeMsg));
      cleanRxBuffer(gWholeMsg); // remove the processed command
    end

    else if ((status = 1) and (gByteCount < gWholeMsg)) then  // not enough bytes to process message...wait for more
    begin
      break;
    end;
  end;// while

  if ((cbfilterGarbage.Checked = false) and (SMsg <> '')) then // is there any garbage data at the end?
    begin                                                   //
      wrMemoWindow(cbxRDXWindowEnable,memoRx,lblReceived,RxWinLimit,RxPlace,'RX ','Lines Received : ',SMsg);
    end;                                   //
end;

procedure TMainForm.decodeRecievedData(s: string);
var
  SMsg      : string;
  lsLineNum : string;
  i         : integer;
  count     : byte;
  cal,giv   : byte;
  DPtr      : pbyte;
  SPtr      : pbyte;
begin
  if length(s) <> 0 then
    begin
    i := 1;
    while i <= length(s) do
      begin
        if (Ord(s[i]) = $FE) then
        begin
          responseFirmware(s);
          i        := i + C2Responselength;
          fImageRedraw := True;
          inc(NumberOfResponse);
        end//case = C5Response
        else
          begin
          i          := i + length(s);
          end;
      end;// while i <= length(s) do
    end;// if length(s) <> 0 then

  wrMemoWindow(cbxRDXWindowEnable,memoRx,lblReceived,RxWinLimit,RxPlace,'RX ','Lines Received : ',s);
end;


procedure TMainForm.tkbRecieveTimeOutChange(Sender: TObject);
begin
  lblRecievedTimeout.Caption := 'Recieve Timeout = ' + IntToStr(tkbRecieveTimeOut.Position);
end;

procedure TMainForm.tkbScrollRateChange(Sender: TObject);
begin
 if tkbScrollRate.Position < tbUpdateRate.Position then
   tbUpdateRate.Position := tkbScrollRate.Position;
 lblScrollRate.caption   := 'Scroll Rate Value: ' + InttoStr(tkbScrollRate.Position);
end;

procedure TMainForm.tkb_DialSliderChange(Sender: TObject);
 const FeetPerStep = (50000/4095);
begin
  if oldSlider <> tkb_DialSlider.Position then
  begin
    if statusFlg = false then
    begin
      lbl_DacValue.Caption := 'DAC VALUE: ' + InttoStr(tkb_DialSlider.Position) +
                              '     ' + IntToHex(tkb_DialSlider.Position,4);
    end
    else
    begin
      statusFlg := false;
    end;
    ScrollDial := tkb_DialSlider.Position;
//    edt_Dial.Text := FloatToStrF((tkb_DialSlider.Position * FeetPerStep / 1000),ffFixed,18,3);
    edt_Dial.Text := InttoStr(tkb_DialSlider.Position);
    edt_Dial.SelectAll;
//    lbl_deg.Caption := 'Cabin Pressure Altitude FT X 1000 = ' + convertDegrees(tkb_DialSlider.Position);
    if (fC0Request = false) then
      fC1Request := true;
    oldSlider := tkb_DialSlider.Position;
    end;
end;

//procedure TMainForm.paintGUI;
//begin
//fImageRedraw := False;
//
//
//end;

// Gui functions
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------



function TMainForm.calculateRate(ct : double;g : Tx;rc : boolean;l : TObject;t : TObject; s : string):Tx;
var
   i   : integer;
   cus : double; // current update speed
   cuh : double; // current update Hz
   cua : double; // current update average
begin
  if (g.us <> 0) and rc then
    begin
    cus := (ct - g.us) * 86400;
    if cus <> 0 then
      begin
      g.ar[g.ai] := cus;
      inc(g.ai);
      if g.ui < 255 then Inc(g.ui);
      cua := 0;
      for i := 0 to (g.ui - 1) do
        begin  cua := cua + g.ar[i];    end;
      cus := cua / g.ui;
      cuh := RoundTo((1 / cus),-2);
      g.s := FloatToStr(cuh) +'Hz';
      g.us := ct;
      end;//if cus <> 0 then
    end// if g.us <> 0 then
  else if rc then
    begin
    g.us := ct;
    g.ai := 0;
    end;//else if g.us <> 0 then
  TLabel(l).Caption := s + g.s + ' ' +  IntToStr(TTrackBar(t).Position);
  Result := g;
end;

procedure TMainForm.cpOutputData(s: string; rc: boolean);
var
   i         : integer;
   count     : byte;
   SMsg      : string;
   lsLineNum : string;
begin
  SMsg       := '';                                                     // start with a clean label to write on.
  if s <> '' then
    begin
    cpDrv.SendString(s);                                                // send the whole string
    //LightTXOnTime := LightOnTime;                                       //
    i        := 1;                                                      //
                                    //
    end;
  wrMemoWindow(cbxTRXWindowEnable,memoTx,lblTransmitted,TxWinLimit,TxPlace,'TX ','Lines Transmitted : ',s);
end;


procedure TMainForm.wrMemoWindow(show,memo,lbl :TObject; limit,place : integer;head,cap,s : string);
var lsLineNum : string;
    i         : integer;
    cnt       : byte;
    SMsg      : string;
begin
  if TCheckBox(show).Checked then
    begin
    cnt := length(s);
    SMsg  := '';
    for i := 1 to cnt do {Loop through the buffer and}
      SMsg  := SMsg + IntToHex(ord(s[i]),2)+' '; {Convert the bytes to a pascal string}

    if TMemo(memo).Lines.Count >= limit then TMemo(memo).Clear;
    lsLineNum := head + IntToStr(TMemo(memo).Lines.Count) + ' -> ';

    While length(lsLineNum) < (place + 7) do
      Insert('0',lsLineNum,4);

    TMemo(memo).Lines.Add(lsLineNum + SMsg);          {then store them in the RX Window }
    TLabel(lbl).Caption := cap + IntToStr(TMemo(memo).Lines.Count);
    end;
end;

procedure TMainForm.memoTxKeyPress(Sender: TObject; var Key: Char);
var UserrecieveString,CharacterCreationString,StringToRecieve : string;
    CharacterPointer,CharacterToRecieve,Stringlength,BadCharPos : byte;

begin
   case Key of
    '0'..'9':;
    'A'..'F':;
    'a'..'f':;
    #8 :;
    #13:begin
        UserrecieveString := memoTx.Lines.Strings[memoTx.Lines.Count-1];
        memoTx.Lines.Delete(memoTx.Lines.Count-1);
        BadCharPos := pos('>',UserrecieveString);
        if BadCharPos <> 0 then
          begin
          memoTx.Lines.Add(UserrecieveString);
          Delete(UserrecieveString,1,BadCharPos+1);
          end;
        While pos(' ',UserrecieveString) <> 0 do
          begin
          BadCharPos := pos(' ',UserrecieveString);
          Delete(UserrecieveString,BadCharPos,1);
          end;//while
        Stringlength := length(UserrecieveString);
        CharacterPointer := 1;
        StringToRecieve := '';
        While CharacterPointer <= Stringlength do
          begin
          CharacterCreationString := '$' + UserrecieveString[CharacterPointer] + UserrecieveString[CharacterPointer+1];
          CharacterToRecieve := StrToInt(CharacterCreationString);
          StringToRecieve := StringToRecieve + Chr(CharacterToRecieve);
          CharacterPointer := CharacterPointer + 2;
          end;
        if StringToRecieve <> '' then
        begin
        parseTx(StringToRecieve);
        end;
        Key := #00;
        end;
    else Key := #00;
  end;//case
end;

procedure TMainForm.parseTx(s : String);
var
    i,j,k         : integer;
    RequestLen    : byte;
begin

end;
//display functions
//***************************************************************************************************************************

//*************************************************************************************************************************
procedure TMainForm.MemoTxChange(Sender: TObject);
begin
  lblTransmitted.Caption := 'Lines Transmitted : ' + IntToStr(memoTx.lines.count);
end;

procedure TMainForm.mm03s01Click(Sender: TObject);
var i : byte;
begin
  mm03s02.Checked           := mm03s01.Checked;
  mm03s01.Checked           := not mm03s01.Checked;
  gRate.ui                  := 0;
  gRate.s                   := '';
  gRate.ai                  := 0;
  gRate.us                  := 0;
  for i := 0 to 255 do
    gRate.ar[i]             := 0;
  gRate.ui                  := 0;
  gRate.uc                  := 0;
  gRateC1                   := gRate;
  gRateC2                   := gRate;
  gRateC3                   := gRate;
  gRateC4                   := gRate;
end;

procedure TMainForm.mm03s03Click(Sender: TObject);
begin
  mm03s03.Checked                 := mm03s04.Checked;
  mm03s04.Checked                 := not mm03s04.Checked;
end;

procedure TMainForm.mm03s05s01Click(Sender: TObject);
begin
  TMenuItem(Sender).Checked       := not TMenuItem(Sender).Checked;
end;



procedure TMainForm.mm04Click(Sender: TObject);
begin
  fC1Request := true;
end;

procedure TMainForm.cpGetData(instr: String);
begin
// Add the string to the recieved lines box with header info
  gSerialBufferSMsg := gSerialBufferSMsg + instr;
  gByteCount := length(gSerialBuffer+gSerialBufferSMsg);
end;

procedure TMainForm.cpDRVReceiveData(Sender: TObject; DataPtr: Pointer;
  DataSize: Cardinal);
var i : integer;
    s : string;
begin
// Convert incoming data into a string
  s := StringOfChar(' ', DataSize);                                      //
  move(DataPtr^, pchar(s)^, DataSize);                                   //
  if s = '' then exit;                                                   //
// Process the buffer line by line.  This breaks the buffer block into discreet lines.
  while s <> '' do                                                       //
  begin
    i := Length(s);
    cpGetData(Copy(s,1,i));                                              // Process the line
    delete(s,1,i);                                                       // then delete it.
  end;
end;

function  TMainForm.cpIntToBaud(baud: integer): string;
begin
  case baud of
     0 : Result :=   '9600';
     1 : Result :=  '19200';
     2 : Result :=  '28800';
     3 : Result :=  '38400';
     4 : Result :=  '57600';
     5 : Result :=  '76800';
     6 : Result :=  '93750';
     7 : Result := '115200';
    else Result :=   '9600';
    end;
end;

function  TMainForm.cpIntToBaudRate(rate: string): TBaudRate;
var irate : integer;
begin
  irate := StrToInt(rate);
  case irate of
       110 : Result := br110;
       300 : Result := br300;
       600 : Result := br600;
      1200 : Result := br1200;
      2400 : Result := br2400;
      4800 : Result := br4800;
      9600 : Result := br9600;
     14400 : Result := br14400;
     19200 : Result := br19200;
     38400 : Result := br38400;
     56000 : Result := br56000;
     57600 : Result := br57600;
    115200 : Result := br115200;
    128000 : Result := br128000;
    256000 : Result := br256000;
    else     Result := brCustom;
    end;
end;

function  TMainForm.cpParityToInt(parity: string): integer;
begin
       if parity = 'none'  then result := 0
  else if parity = 'odd'   then result := 1
  else if parity = 'even'  then result := 2
  else if parity = 'mark'  then result := 3
  else if parity = 'space' then result := 4
  else                          result := 0;
end;

function TMainForm.cpIntToParity(parity: TParity): string;
begin
  case Ord(parity) of
     1 : Result := 'odd';
     2 : Result := 'even';
     3 : Result := 'mark';
     4 : Result := 'space';
    else Result := 'none';
    end;
end;

function TMainForm.cpIntToStopBits(stopbits: TStopBits): string;
begin
  case Ord(stopbits) of
     1 : Result := '1.5';
     2 : Result := '2';
    else Result := '1';
    end;
end;

function  TMainForm.cpStopBitsToInt(stopbits: string): integer;
begin
       if stopbits = '1'   then result := 0
  else if stopbits = '1.5' then result := 1
  else if stopbits = '2'   then result := 2
  else                          result := 0;
end;

procedure TMainForm.saveSettings;
var
  sini     : TIniFile;
begin
SIni := TIniFile.Create(ChangeFileExt(Application.ExeName,'.ini'));
    try
           Sini.WriteString(InstSec, InstSeck01, gPort);                             // Save the open com port
           Sini.WriteString(InstSec, InstSecK02, gBaud);                             // Set the default baud rate for startup
           Sini.WriteString(InstSec, InstSecK03, InttoStr(gAddress));                             // Set the default baud rate for startup
           Sini.WriteString(GENSec,  GenSecK03,  gDataBits);                         // Set the default Data word length
           Sini.WriteString(GENSec,  GenSecK04,  gStopBits);                         // Set the default Parity mode for startup
           Sini.WriteString(InstSec, GenSecK05,  gParity);                           // Set the default Number of Stop bits
    finally
           Sini.Free;
    end;
end;

procedure TMainForm.parseFont(memo: TRichEdit; sf,section,key: string; sini: TIniFile);
begin
  if(sf = '')then
    begin
    sf                        :=                sini.ReadString(section, key, dsf);
    if(sf = '')then
      begin
      sf                      :=                dsf;
      end;
    end;
  memo.Lines.Delimiter        :=                ',';
  memo.Lines.DelimitedText    :=                sf;
  memo.Font.Name              :=                memo.Lines.Strings[0];
  memo.Font.Size              :=                StrToInt(memo.Lines.Strings[1]);
  memo.Font.Color             :=                StringToColor(memo.Lines.Strings[2]);
  memo.Color                  :=                StringToColor(memo.Lines.Strings[3]);
  memo.Clear;
end;

procedure TMainForm.cpSetComPort;
var i        : integer;                                       //
begin
  if cpDrv.Connected then                                     // check to make sure the port is closed
    begin
    cpDrv.Disconnect;                                         // disconnect the com port
    //setColorCOMLightsOff;                                     // deactivate comm line lights
    end;
//  gParity := 'none';

  cpDrv.PortName            := '\\.\'+gPort;                  // assign the port
  cpDrv.BaudRate            := cpIntToBaudRate(gBaud);        // set the baud rate
  cpDrv.BaudRateValue       := StrToInt(gBaud);               // set the default baud rate
  cpDrv.Parity              := TParity(cpParityToInt(gParity));// set the parity
  cpDrv.Databits            := TDataBits(StrToInt(gDataBits));// set the number of data bits
  cpDrv.StopBits            := TStopBits(cpStopBitsToInt(gStopBits)); // set the number of stop bits

  CPDrv.HwFlow              := THwFlowControl(0);             //
  CPDrv.SwFlow              := TSwFlowControl(0);             //
  CPDrv.EnableDTROnOpen     := False;                         //
  CPDrv.CheckLineStatus     := False;                         //
  CPDrv.InBufSize           := 65536;                         //
  CPDrv.OutBufSize          := 2048;                          //
  //setColorCOMLightsOff;                                       // deactivate comm line lights
  try
    cpDrv.Connect;                                            // open the com port
    mm04.Enabled            := cpDrv.Connected;               // deactivate all comport dependent menu functions
    if mm04.Enabled then                                      // make sure that the port is open
      begin
      saveSettings;                                           // save new settings to INI file
      mm04.Enabled          := True;                          // set the status menu item to active
      end
    else
      MessageDlg('Error Port Not Opened Properly!',mtError,[mbOk],0);
  except
    MessageDlg('Error Port Not Opened Properly!',mtError,[mbOk],0);
  end;
  mm03.Enabled              := mm04.Enabled;                  // enable the menu item if the com port was opened
  mm05.Enabled              := mm04.Enabled;                  // enable the menu item if the com port was opened

  Application.ShowHint      := True;                          // enable the messaging
  MainForm.Caption          := buildMainCaption;              // show the com port settings on the main form bar
  cbValidPorts.Text         := gPort;                         //
  cbBaudRate.Text           := gBaud;                         //
end;

function TMainForm.buildMainCaption: string;
var s,s2 : string;
begin
    s := InstRevInf;
    if cpDrv.Connected then
    begin
     s2 := '   ' + cpDrv.PortName;
     s2 := AnsiUpperCase(s2);
     Delete(s2, 1, pos('C',s2)-1);

     s := s + ' ' + s2 + ' ';
     case ord(cpDrv.BaudRate) of
       1  : s := s + ' 110';    //       br110
       2  : s := s + ' 300';    //       br300
       3  : s := s + ' 600';    //       br600
       4  : s := s + ' 1200';   //       br1200
       5  : s := s + ' 2400';   //       br2400
       6  : s := s + ' 4800';   //       br4800
       7  : s := s + ' 9600';   //       br9600
       8  : s := s + ' 14400';  //       br14400
       9  : s := s + ' 19200';  //       br19200
       10 : s := s + ' 38400';  //       br38400
       11 : s := s + ' 56000';  //       br56000
       12 : s := s + ' 57600';  //       br57600
       13 : s := s + ' 115200'; //       br115200
       14 : s := s + ' 128000'; //       br128000
       15 : s := s + ' 256000'; //       br256000
       else s := s + ' ' + IntToStr(cpDrv.BaudRateValue);
     end;
     s := s + ',' + IntToStr(5+ord(cpDrv.DataBits)) + ',1';

     s := s + ',' + cpIntToStopBits(cpDrv.StopBits);
//     case ord(cpDrv.StopBits) of
//       0  :  s := s + ',1';
//       1  :  s := s + ',1.5';
//       2  :  s := s + ',2';
//      else   s := s + ',Error';
//     end;
     s := s + ',' + cpIntToParity(cpDrv.Parity);
//     case ord(cpDrv.Parity) of
//       0  :  s := s + ',Even';
//       1  :  s := s + ',Mark';
//       2  :  s := s + ',None';
//       3  :  s := s + ',Odd';
//       4  :  s := s + ',Space';
//       else  s := s + ',Error';
//     end;
    end
  else
    begin
    s := s + ' com port not connected';
    end;
  Result := s;
end;

procedure TMainForm.scrollEverything();
begin
  tkb_DialSlider.Position := scrollDial;

  if ScrollDir then ScrollDial  := ScrollDial + 5 
  else ScrollDial := ScrollDial - 5;

  if ScrollDial >= 4095 then ScrollDir := False
  else if ScrollDial <= 0 then ScrollDir := True;
       
end;

end.
