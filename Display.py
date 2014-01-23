#!/usr/bin/env python      
import Tkinter as tk       

class Display(tk.Frame):              
    def __init__(self, master=None):
        tk.Frame.__init__(self, master)   
        self.grid()                       
        self.createWidgets()

	logo = tk.PhotoImage('arrow.png')
	tk.Label(image=logo).grid()

    def createWidgets(self):
        self.quitButton = tk.Button(self, text='Quit', command=self.quit)            
        self.quitButton.grid()            

app = Display()                       
app.master.title('Sample application')    
app.mainloop()                         
