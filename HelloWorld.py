import wx
import wx.grid as gridlib
import ctffind
import os
########################################################################
class LeftPanel(wx.Panel):
    """"""
 
    #----------------------------------------------------------------------
    def __init__(self, parent):
        """Constructor"""
        wx.Panel.__init__(self, parent=parent)
 
       
        self.panel = wx.Panel(self)     
        self.cs = wx.StaticText(self.panel, label="CS")
        self.cs_result = wx.TextCtrl(self.panel, size=(140, -1))
        self.ht = wx.StaticText(self.panel, label="HT")
        self.ht_result = wx.TextCtrl(self.panel, size=(140, -1))
        self.ampcnst=wx.StaticText(self.panel, label="ampcnst")
        self.ampcnst_result = wx.TextCtrl(self.panel, size=(140, -1))

        

        self.xmag=wx.StaticText(self.panel, label="XMAG")
        self.xmag_result = wx.TextCtrl(self.panel, size=(140, -1))
        self.button = wx.Button(self.panel, label="Run")
        self.dstep=wx.StaticText(self.panel, label="dstep")
        self.dstep_result = wx.TextCtrl(self.panel, size=(140, -1))

        self.box=wx.StaticText(self.panel, label="box")
        self.box_result = wx.TextCtrl(self.panel, size=(140, -1))
        self.resmin=wx.StaticText(self.panel, label="resmin")
        self.resmin_result = wx.TextCtrl(self.panel, size=(140, -1))

        self.resmax=wx.StaticText(self.panel, label="resmax")
        self.resmax_result = wx.TextCtrl(self.panel, size=(140, -1))
        self.dfmin=wx.StaticText(self.panel, label="dfmin")
        self.dfmin_result = wx.TextCtrl(self.panel, size=(140, -1))

        self.dfmax=wx.StaticText(self.panel, label="dfmax")
        self.dfmax_result = wx.TextCtrl(self.panel, size=(140, -1))
        self.fstep=wx.StaticText(self.panel, label="fstep")
        self.fstep_result = wx.TextCtrl(self.panel, size=(140, -1))

        self.dast=wx.StaticText(self.panel, label="dast")
        self.dast_result = wx.TextCtrl(self.panel, size=(140, -1))
        self.inputfile=wx.StaticText(self.panel, label="inputfile")
        self.inputfile_result = wx.TextCtrl(self.panel, size=(140, -1))
        self.outputfile=wx.StaticText(self.panel, label="outputfile")
        self.outputfile_result = wx.TextCtrl(self.panel, size=(140, -1))
        self.result = wx.StaticText(self.panel, label="")
        #self.editname = wx.TextCtrl(self.panel, size=(140, -1))

        # Set sizer for the frame, so we can change frame size to match widgets
        self.windowSizer = wx.BoxSizer()
        self.windowSizer.Add(self.panel, 1, wx.ALL | wx.EXPAND)        

        # Set sizer for the panel content
        self.sizer = wx.GridBagSizer(15, 15)
        self.sizer.Add(self.cs, (0, 0))
        self.sizer.Add(self.cs_result, (0, 1))
        self.sizer.Add(self.ht, (1, 0))
        self.sizer.Add(self.ht_result, (1, 1))
        self.sizer.Add(self.ampcnst, (2, 0))
        self.sizer.Add(self.ampcnst_result, (2, 1))
        self.sizer.Add(self.xmag, (3, 0))
        self.sizer.Add(self.xmag_result, (3, 1))
        self.sizer.Add(self.dstep, (4, 0))
        self.sizer.Add(self.dstep_result, (4, 1))
        self.sizer.Add(self.box, (5, 0))
        self.sizer.Add(self.box_result, (5, 1))
        self.sizer.Add(self.resmin, (6, 0))
        self.sizer.Add(self.resmin_result, (6, 1))
        self.sizer.Add(self.resmax, (7, 0))
        self.sizer.Add(self.resmax_result, (7, 1))
        self.sizer.Add(self.dfmin, (8, 0))
        self.sizer.Add(self.dfmin_result, (8, 1))
        self.sizer.Add(self.dfmax, (9, 0))
        self.sizer.Add(self.dfmax_result, (9, 1))
        self.sizer.Add(self.fstep, (10, 0))
        self.sizer.Add(self.fstep_result, (10, 1))
        self.sizer.Add(self.dast, (11, 0))
        self.sizer.Add(self.dast_result, (11, 1))
        self.sizer.Add(self.inputfile, (12, 0))
        self.sizer.Add(self.inputfile_result, (12, 1))
        self.sizer.Add(self.outputfile, (13, 0))
        self.sizer.Add(self.outputfile_result, (13, 1))
        self.sizer.Add(self.result, (15, 1))
        self.sizer.Add(self.button, (14, 0), flag=wx.EXPAND)
        

        

        # Set simple sizer for a nice border
        self.border = wx.BoxSizer()
        self.border.Add(self.sizer, 1, wx.ALL | wx.EXPAND, 5)

        # Use the sizers
        self.panel.SetSizerAndFit(self.border)  
        self.SetSizerAndFit(self.windowSizer)  
        self.Fit()
     
        # Set event handlers
       # self.button.Bind(wx.EVT_BUTTON, self.OnButton)
        #self.Show()
        #self.child.res.SetLabel(self.cs_result.GetValue()) 
        
        

########################################################################
class RightPanel(wx.Panel):
    """"""
 
    #----------------------------------------------------------------------
    def __init__(self, parent):
        """Constructor"""
        wx.Panel.__init__(self, parent=parent)
        self.SetBackgroundColour("white") 
        self.panel = wx.Panel(self) 
        self.panel.SetBackgroundColour(wx.WHITE)

        
        img = wx.EmptyImage(240,240)
        self.imageCtrl = wx.StaticBitmap(self.panel, wx.ID_ANY, 
                                         wx.BitmapFromImage(img))
        self.windowSizer = wx.BoxSizer()
        self.windowSizer.Add(self.panel, 1, wx.ALL | wx.EXPAND)        

        # Set sizer for the panel content
        self.sizer = wx.BoxSizer(wx.VERTICAL)
        #self.sizer.Add(self.results, (0, 0))
        
        #self.sizer.Add(self.png, (1, 0))
        self.sizer.Add(self.imageCtrl, 0, wx.ALL, 5)
                # Set simple sizer for a nice border
        self.border = wx.BoxSizer()
        self.border.Add(self.sizer, 1, wx.ALL | wx.EXPAND, 5)

        # Use the sizers
        self.panel.SetSizerAndFit(self.border)  
        self.SetSizerAndFit(self.windowSizer)  

        #txt = wx.TextCtrl(self)
 

########################################################################
class MyForm(wx.Frame):
 
    #----------------------------------------------------------------------
    def __init__(self):
        wx.Frame.__init__(self, None, title="Splitter Tutorial")
 
        splitter = wx.SplitterWindow(self)
        self.leftP = LeftPanel(splitter)
        self.rightP = RightPanel(splitter)
 
        # split the window
        splitter.SplitVertically(self.leftP,self.rightP)
        splitter.SetMinimumPaneSize(200)
 
        sizer = wx.BoxSizer(wx.VERTICAL)
        sizer.Add(splitter, 1, wx.EXPAND)
        self.SetSizer(sizer)
        self.SetSizer(sizer)
        self.leftP.button.Bind(wx.EVT_BUTTON, self.OnButton)
        
    
    def OnButton(self, event):
        #print 'bindin'
        #self.rightP.results.SetLabel(self.leftP.cs_result.GetValue())
        c2=ctffind.CTFFind(float(self.leftP.cs_result.GetValue()),float(self.leftP.ht_result.GetValue()),float(self.leftP.ampcnst_result.GetValue()),
            float(self.leftP.xmag_result.GetValue()),float(self.leftP.dstep_result.GetValue()),float(self.leftP.resmin_result.GetValue()),
            float(self.leftP.resmax_result.GetValue()),float(self.leftP.dfmin_result.GetValue()),float(self.leftP.dfmax_result.GetValue()),
            float(self.leftP.fstep_result.GetValue()),float(self.leftP.dast_result.GetValue()),int(self.leftP.box_result.GetValue()),
            str(self.leftP.inputfile_result.GetValue()),str(self.leftP.outputfile_result.GetValue()))
        a=self.leftP.outputfile_result.GetValue()
        filepath=a[:-4]+'.png'
        os.system('proc2d '+a+' '+filepath)
        #filepath = 'lo.png'
        img = wx.Image(filepath, wx.BITMAP_TYPE_ANY)
        
        self.rightP.imageCtrl.SetBitmap(wx.BitmapFromImage(img)) 
        
        

#----------------------------------------------------------------------
# Run the program
if __name__ == "__main__":
    app = wx.App(False)
    frame = MyForm()
    frame.Show()
    app.MainLoop()