
'''
A4 Python GUI for iCalendar
Giavinh Lam
08/11/2017
Many tkinter GUI code examples were used/taken/studied in the Programming Python (4th ed) textbook by M. Lutz
'''

import tkinter
from tkinter import filedialog
from datetime import datetime
from pathlib import Path
from tkinter import messagebox
from tkinter.ttk import *
from tkinter import *
from ctypes import *

class Calendar(Structure):
    _fields_ = [
        ("version", c_float),
        ("prodID", c_byte * 1000),
        ("events", c_void_p),
        ("properties", c_void_p)]

class DateTime(Structure):
    _fields_ = [
        ("date", c_byte * 9),
        ("time", c_byte * 7),
        ("UTC", c_bool)]

class Event(Structure):
    _fields_ = [
        ("creationDateTime", DateTime),
        ("startDateTime", DateTime),
        ("properties", c_void_p),
        ("alarms", c_void_p)]

root = Tk()
root.title("iCalGUI")
ws = root.winfo_screenwidth() #width of screen
hs = root.winfo_screenheight() #height of screen
x = (ws/2) - (1000/2)
y = (hs/2) - (700/2)
root.geometry('%dx%d+%d+%d' % (1000, 700, x, y))
menubar = Menu(root)
activenode = 0
treeWidget = 0

#Python to C interlopability stuff
filename = None
calendarString = None
eventCount = 0
event = 0
summary = None
alarms = 0
indexString = 0 #represents beginning of event
indexString2 = 0 #represents end of event
originalString = None
newString = None
calendarOpen = 0
eventCreation = 0
calCreation = 0
eventCounter = 1
fStr = None

def closeVerify():
	if messagebox.askokcancel("Quit", "Are you sure you want to quit?"):
		root.destroy()
		if calendarOpen == 1:
			deleteCal = CDLL(libPath).deleteCalendar
			deleteCal.argtypes = [POINTER(Calendar)]
			deleteCal(calPtr)

def quit(event=NONE):
	if messagebox.askokcancel("Quit", "Are you sure you want to quit?"):
		root.destroy()
		if calendarOpen == 1:
			deleteCal = CDLL(libPath).deleteCalendar
			deleteCal.argtypes = [POINTER(Calendar)]
			deleteCal(calPtr)

def makeCString(str):
    utf8Str = str.encode('utf-8')
    cStr = c_char_p(utf8Str) #c_char_p() is a Ctypes function for createing a value of type c_char_p
    return cStr


libPath = './bin/icallib.so'
libc = CDLL(libPath)
#createCal = libc.createCalendar
#createCal.argtypes = [c_char_p,POINTER(POINTER(Calendar))]
#createCal.restype = c_int
printCal = libc.printCalendar
printCal.argtypes = [POINTER(Calendar)] #this can also be commented out
printCal.restype = c_char_p             #this CANNOT be commented out! Otherwise Python will decide that printCal returns an int!
calPtr = POINTER(Calendar)()
def fileOpen(event=NONE):
	global calFile
	global filename
	global calendarString
	global createCal
	global libc
	global libPath
	global calPtr
	global calendarOpen
	global string
	global originalString
	global tv
	global fStr
	global eventCounter
	global calCreation

	root.filename = filedialog.askopenfilename(initialdir = "./",title = "Select file",filetypes = (("iCal files","*.ics"),("all files","*.*")))

	logView.config(state=NORMAL)
	if not root.filename:
		logView.insert(INSERT, "\nFile opening canceled.\n")
	else:
		filename = root.filename

		if filename != None:
			if fStr != None:
				originalString = fStr

			logView.config(state=NORMAL)
			logView.insert(INSERT, "\n" + filename + " opened\n")
			fStr = filename.encode('utf-8')
			createCal = libc.createCalendar
			createCal.argtypes = [c_char_p,POINTER(POINTER(Calendar))]
			createCal.restype = c_int
			string = createCal(fStr,byref(calPtr)) #notice the type

			tv.delete(*tv.get_children())
			if string == 0:
				logView.insert(INSERT, "CALENDAR CREATION STATUS: OK\n")
				calStr = printCal(calPtr)
				calendarString = calStr.decode("utf-8")
				calCreation = 0
				eventCounter = 1
				parseCal()
				root.title(filename)
				create.entryconfig("Create event", state="normal")
				calendarOpen = 1
			else:
				logView.insert(INSERT, "CALENDAR CREATION STATUS: ")
				if string == 1:
					logView.insert(INSERT, "INV_FILE\n")
				elif string == 2:
					logView.insert(INSERT, "INV_CAL\n")
				elif string == 3:
					logView.insert(INSERT, "INV_VER\n")
				elif string == 4:
					logView.insert(INSERT, "DUP_VER\n")
				elif string == 5:
					logView.insert(INSERT, "INV_PRODID\n")
				elif string == 6:
					logView.insert(INSERT, "DUP_PRODID\n")
				elif string == 7:
					logView.insert(INSERT, "INV_EVENT\n")
				elif string == 8:
					logView.insert(INSERT, "INV_CREATEDT\n")
				elif string == 9:
					logView.insert(INSERT, "INV_ALARM\n")
				elif string == 10:
					logView.insert(INSERT, "INV_WRITE_ERROR\n")
				else:
					logView.insert(INSERT, "OTHER_ERROR\n")
				
				if originalString != None and calendarOpen == 1:
					#print('hello')
					#deleteCal = CDLL(libPath).deleteCalendar
					#deleteCal.argtypes = [POINTER(Calendar)]
					#deleteCal(calPtr)
					calPtr = POINTER(Calendar)()
					string = createCal(originalString,byref(calPtr))
					calStr = printCal(calPtr)
					calendarString = calStr.decode("utf-8")
					parseCal()

				calendarOpen = 0

			showAlarm.place_forget()
			optionalProp.place_forget()
					#calendarString = calStr.decode("utf-8")
					#parseCal()
	#else:
	#	logView.insert(INSERT, "No filename given.\n")

	logView.see('end') #automatic scroll essentially
	logView.config(state=DISABLED)

def saveasFile(event=NONE): #possible bug if you do saves from different directories #asks for confirmation twice lol
	global filename
	global calCreation
	logView.config(state=NORMAL)
	logView.insert(INSERT, "Attemping to save... \n")

	if not filename and calCreation == 0:
		logView.insert(INSERT, "No calendar currently open. Unable to save.\n")
	else:
		validateCal = libc.validateCalendar
		validateCal.argtypes = [POINTER(Calendar)]
		validateCal.restype = c_int
		valStr = validateCal(calPtr)
		#validateString = valStr.decode("utf-8")
		logView.insert(INSERT, "Calendar Validation Status: ")
		if valStr == 0:
			logView.insert(INSERT, "OK\n")
			root.filename =  filedialog.asksaveasfilename(initialdir = "./",title = "Select file",filetypes = (("iCal files","*.ics"),("all files","*.*")))
			filename = root.filename
			#my_file = Path(filename)
			if filename:
				writeCal = libc.writeCalendar
				writeCal.argtypes = [c_char_p, POINTER(Calendar)]
				writeCal.restype = c_int
				fStr = filename.encode('utf-8')
				writeStr = writeCal(fStr, calPtr)
				if writeStr == 0:
					logView.insert(INSERT, "Calendar Saving Status: OK\n")
					root.title(filename)
				else:
					logView.insert(INSERT, "Calendar Saving Status: WRITE_ERROR\n")

			else:
				logView.insert(INSERT, "Calendar Saving canceled.\n")
			
		else:
			if valStr == 1:
				logView.insert(INSERT, "INV_FILE\n")
			elif valStr == 2:
				logView.insert(INSERT, "INV_CAL\n")
			elif valStr == 3:
				logView.insert(INSERT, "INV_VER\n")
			elif valStr == 4:
				logView.insert(INSERT, "DUP_VER\n")
			elif valStr == 5:
				logView.insert(INSERT, "INV_PRODID\n")
			elif valStr == 6:
				logView.insert(INSERT, "DUP_PRODID\n")
			elif valStr == 7:
				logView.insert(INSERT, "INV_EVENT\n")
			elif valStr == 8:
				logView.insert(INSERT, "INV_CREATEDT\n")
			elif valStr == 9:
				logView.insert(INSERT, "INV_ALARM\n")
			elif valStr == 10:
				logView.insert(INSERT, "INV_WRITE_ERROR\n")
			else:
				logView.insert(INSERT, "OTHER_ERROR\n")
			logView.insert(INSERT, "Unable to save.\n")

	logView.see('end') #automatic scroll essentially
	logView.config(state=DISABLED)
   
def saveFile(event=NONE):
	global filename
	global calCreation
	global calptr
	if not filename or calCreation == 1:
		saveasFile()
	else:
		logView.config(state=NORMAL)
		logView.insert(INSERT, "Attemping to save... \n")
		validateCal = libc.validateCalendar
		validateCal.argtypes = [POINTER(Calendar)]
		validateCal.restype = c_int
		valStr = validateCal(calPtr)
		#validateString = valStr.decode("utf-8")
		logView.insert(INSERT, "Calendar Validation Status: ")

		if valStr == 0:
			logView.insert(INSERT, "OK\n")
			writeCal = libc.writeCalendar
			writeCal.argtypes = [c_char_p, POINTER(Calendar)]
			writeCal.restype = c_int
			fStr = filename.encode('utf-8')
			writeStr = writeCal(fStr, calPtr)
			if writeStr == 0:
				logView.insert(INSERT, "Calendar Saving Status: OK\n")
			else:
				logView.insert(INSERT, "Calendar Saving Status: WRITE_ERROR\n")
		else:
			if valStr == 1:
				logView.insert(INSERT, "INV_FILE\n")
			elif valStr == 2:
				logView.insert(INSERT, "INV_CAL\n")
			elif valStr == 3:
				logView.insert(INSERT, "INV_VER\n")
			elif valStr == 4:
				logView.insert(INSERT, "DUP_VER\n")
			elif valStr == 5:
				logView.insert(INSERT, "INV_PRODID\n")
			elif valStr == 6:
				logView.insert(INSERT, "DUP_PRODID\n")
			elif valStr == 7:
				logView.insert(INSERT, "INV_EVENT\n")
			elif valStr == 8:
				logView.insert(INSERT, "INV_CREATEDT\n")
			elif valStr == 9:
				logView.insert(INSERT, "INV_ALARM\n")
			elif valStr == 10:
				logView.insert(INSERT, "INV_WRITE_ERROR\n")
			else:
				logView.insert(INSERT, "OTHER_ERROR\n")
			logView.insert(INSERT, "Unable to save.\n")

	logView.see('end') #automatic scroll essentially
	logView.config(state=DISABLED)

def parseCal():
	global calendarString
	global indexString
	global indexString2
	global eventCount
	global originalString
	global newString
	global splitString
	global eventCreation
	global eventCounter

	if eventCreation == 1:
		eventCreation = 1
		eventCounter = eventCounter + 1
		tv.insert('', 'end', text=eventCounter, values=('0', '0','None'))
	else:	
		eventCount = calendarString.lower().count("$*%*$")
		splitString = calendarString.split('$*%*$')
		i = 0
		while i != eventCount:
			if splitString[i].lower().find("summary:") == -1:
				tv.insert('', 'end', text=i+1, values=(splitString[i][1], splitString[i][0],'None'))
			else:
				tv.insert('', 'end', text=i+1, values=(splitString[i][len(splitString[i])-1], splitString[i][len(splitString[i])-2], splitString[i][:len(splitString[i])-2]))
			
			i = i + 1
			if calCreation != 1:
				eventCounter = eventCounter + 1

def createCalY(self):
	global calPtr
	global calStr
	global calendarString
	global calCreation
	global eventCounter
	global eventCreation
	dtCount = 0
	if e1.get() == '' or e2.get() == '':
		if e1.get() == '':
			messagebox.showwarning("Product ID Missing","Must fill in Calendar Product ID!", parent=self)
		elif e2.get() == '':
			messagebox.showwarning("Event ID Missing","Must fill in Event User ID!", parent=self)
	else:
		if e3.get() != '':
			dtCount = 1
			testdtstart = e3.get()

		if dtCount == 1:
			if len(testdtstart) == 15 or len(testdtstart) == 16:
				teststring1 = testdtstart[0:8]
				teststring2 = testdtstart[9:]
				if testdtstart[8] == 'T' and teststring1.isdigit():
					inputText = ((c_char * 1000) * 4)()
					inputText[0].value = e1.get().encode('ISO-8859-1')
					inputText[1].value = e2.get().encode('ISO-8859-1')
					inputText[2].value = e3.get().encode('ISO-8859-1')
					inputText[3].value = e4.get().encode('ISO-8859-1')
					calCreation = 1
					root.title("iCalGUI")
					tv.delete(*tv.get_children())
					createSCal = libc.createSimpleCal
					createSCal.restype = POINTER(Calendar)
					newCalPtr = createSCal(inputText)
					##validateCal = libc.validateCalendar
					#validateCal.argtypes = [POINTER(Calendar)]
					#validateCal.restype = c_int
					#valStr = validateCal(newCalPtr)
					#calPtr = newCalPtr
					#print(valStr)
					calStr = printCal(newCalPtr)
					eventCounter = 1
					eventCreation = 0
					calendarString = calStr.decode("utf-8")
					parseCal()
					logView.config(state=NORMAL)
					logView.insert(INSERT, "Calendar created.\n")
					logView.see('end')
					logView.config(state=DISABLED)
					create.entryconfig("Create event", state="normal")
					self.grab_release()
					self.destroy()
				else:
					messagebox.showwarning("Invalid DTSTART","Format: YYYYMMDDTHHMMSS (ex. 19971020T080000).", parent=self)
				
			else:
				messagebox.showwarning("Invalid DTSTART","Format: YYYYMMDDTHHMMSS (ex. 19971020T080000).", parent=self)
		else:
			inputText = ((c_char * 1000) * 4)()
			inputText[0].value = e1.get().encode('ISO-8859-1')
			inputText[1].value = e2.get().encode('ISO-8859-1')
			inputText[2].value = e3.get().encode('ISO-8859-1')
			inputText[3].value = e4.get().encode('ISO-8859-1')
			calCreation = 1
			root.title("iCalGUI")
			tv.delete(*tv.get_children())
			createSCal = libc.createSimpleCal
			createSCal.restype = POINTER(Calendar)
			newCalPtr = createSCal(inputText)
			calPtr = newCalPtr
			calStr = printCal(newCalPtr)
			eventCounter = 1
			eventCreation = 0
			calendarString = calStr.decode("utf-8")
			parseCal()
			create.entryconfig("Create event", state="normal")
			logView.config(state=NORMAL)
			logView.insert(INSERT, "Calendar created.\n")
			logView.see('end')
			logView.config(state=DISABLED)
			self.grab_release()
			self.destroy()

def createCalN(self, event=NONE):
	logView.config(state=NORMAL)
	logView.insert(INSERT, "Exited popup...\n")
	logView.see('end')
	logView.config(state=DISABLED)
	self.grab_release()
	self.destroy()

def close(self):
	logView.config(state=NORMAL)
	logView.insert(INSERT, "Exited popup...\n")
	logView.see('end')
	logView.config(state=DISABLED)
	self.grab_release()
	self.destroy()

def createCal():
	global e1
	global e2
	global e3
	global e4
	#global e5

	logView.config(state=NORMAL)
	logView.insert(INSERT, "Initiating Calendar Creation...\n")
	logView.see('end')
	logView.config(state=DISABLED)

	new = Toplevel()
	Label(new, text="Product ID").grid(row=0)
	Label(new, text="Event User ID").grid(row=1)
	Label(new, text="DTSTART").grid(row=2)
	#Label(new, text="Date End").grid(row=3)
	Label(new, text="DTSTAMP").grid(row=3)


	e1 = Entry(new)
	e2 = Entry(new)
	e3 = Entry(new)
	e4 = Entry(new)
	#e5 = Entry(new)

	e1.grid(row=0, column=1)
	e2.grid(row=1, column=1)
	e3.grid(row=2, column=1)
	e4.grid(row=3, column=1)
	#e5.grid(row=4, column=1)

	e4.insert(0,datetime.now().strftime('%Y%m%dT%H%M%S'))
	e4.configure(state='readonly')

	createButton = Button(new, text="Create Calendar", command=lambda: createCalY(new)).grid(padx='4', row=6, column=0, rowspan=1)
	cancelButton = Button(new, text="Cancel Calendar", command=lambda: createCalN(new)).grid(row=6, column=1)
	
	w = root.winfo_width()
	h = root.winfo_height()
	test1 = root.winfo_x()
	test2 = root.winfo_y()
	new.bind('<Escape>', lambda x:close(new))

	new.resizable(0,0)
	new.title("iCalendar v2.0 Creation")
	new.protocol("WM_DELETE_WINDOW", lambda: createCalN(new))

	new.geometry('%dx%d+%d+%d' % (300, 115, test1 + w/2 - 300/2, test2 + h/2 - 115/2))
	new.focus()
	new.grab_set()
	new.lift()

def createEventY(self):
	global eventCreation
	dtCount = 0;
	if e4.get() == '':
		messagebox.showwarning("Event ID Missing","Must fill in Event User ID!", parent=self)
	else:
		if e5.get() != '':
			dtCount = 1
			testdtstart = e5.get()

		if dtCount == 1:
			#print(testdtstart)
			#print(len(testdtstart))
			#print(testdtstart[8])
			if len(testdtstart) == 15 or len(testdtstart) == 16:
				teststring1 = testdtstart[0:8]
				teststring2 = testdtstart[9:]
				#print('strng1',teststring1)
				#print('strn1',teststring2)
				if testdtstart[8] == 'T' and teststring1.isdigit():
					inputText = ((c_char * 1000) * 3)()
					inputText[0].value = e4.get().encode('ISO-8859-1')
					inputText[1].value = e5.get().encode('ISO-8859-1')
					inputText[2].value = e6.get().encode('ISO-8859-1')

					createE = libc.createEvent
					#createSCal.restype = POINTER(Calendar)
					createE.restype = POINTER(Calendar)
					newCalPtr = createE(inputText, byref(calPtr))
					eventCreation = 1
					calStr = printCal(newCalPtr)
					calendarString = calStr.decode("utf-8")
					#tv.delete(*tv.get_children())
					parseCal()
					create.entryconfig("Create event", state="normal")
					logView.config(state=NORMAL)
					logView.insert(INSERT, "Event created.\n")
					logView.see('end')
					logView.config(state=DISABLED)
					self.grab_release()
					self.destroy()
				else:
					messagebox.showwarning("Invalid DTSTART","Format: YYYYMMDDTHHMMSS (ex. 19971020T080000).", parent=self)
			else:
				messagebox.showwarning("Invalid DTSTART","Format: YYYYMMDDTHHMMSS (ex. 19971020T080000).", parent=self)
		else:
			inputText = ((c_char * 1000) * 3)()
			inputText[0].value = e4.get().encode('ISO-8859-1')
			inputText[1].value = e5.get().encode('ISO-8859-1')
			inputText[2].value = e6.get().encode('ISO-8859-1')
			createE = libc.createEvent
				#createSCal.restype = POINTER(Calendar)
			createE.restype = POINTER(Calendar)
			newCalPtr = createE(inputText, byref(calPtr))

			calStr = printCal(newCalPtr)
			calendarString = calStr.decode("utf-8")
			#tv.delete(*tv.get_children())
			eventCreation = 1
			parseCal()
			create.entryconfig("Create event", state="normal")
			logView.config(state=NORMAL)
			logView.insert(INSERT, "Event created.\n")
			logView.see('end')
			logView.config(state=DISABLED)
			self.grab_release()
			self.destroy()

def createEventN(self, event=NONE):
	self.grab_release()
	self.destroy()

def createnewEvent():
	global e4
	global e5
	global e6
	#global e7

	logView.config(state=NORMAL)
	logView.insert(INSERT, "Initiating Event Creation...\n")
	logView.see('end')
	logView.config(state=DISABLED)

	newE = Toplevel()
	Label(newE, text="Event User ID").grid(row=0)
	Label(newE, text="Event Start Time").grid(row=1)
	#Label(newE, text="Event End Time").grid(row=2)
	Label(newE, text="DTSTAMP").grid(row=2)

	e4 = Entry(newE)
	e5 = Entry(newE)
	e6 = Entry(newE)
	#e7 = Entry(newE)

	e4.grid(row=0, column=1)
	e5.grid(row=1, column=1)
	e6.grid(row=2, column=1)
	#e7.grid(row=3, column=1)

	e6.insert(0,datetime.now().strftime('%Y%m%dT%H%M%S'))
	e6.configure(state='readonly')

	createButton = Button(newE, text="Create Event", command=lambda: createEventY(newE)).grid(padx='4', row=4, column=0, rowspan=1)
	cancelButton = Button(newE, text="Cancel Event", command=lambda: createEventN(newE)).grid(row=4, column=1)
	
	w = root.winfo_width()
	h = root.winfo_height()
	test1 = root.winfo_x()
	test2 = root.winfo_y()

	newE.bind('<Escape>', lambda x:close(newE))

	newE.resizable(0,0)
	newE.title("iCalendar Event Creation")
	newE.protocol("WM_DELETE_WINDOW", lambda: createCalN(newE))
	newE.geometry('%dx%d+%d+%d' % (286, 95, test1 + w/2 - 286/2, test2 + h/2 - 95/2))
	newE.focus()
	newE.grab_set()
	newE.lift()
	

def helpPopup():
	top = Toplevel()

	w = root.winfo_width()
	h = root.winfo_height()
	test1 = root.winfo_x()
	test2 = root.winfo_y()

	top.geometry('%dx%d+%d+%d' % (140, 110, test1 + w/2 - 140/2, test2 + h/2 - 110/2))

	top.title("About")
	msg = Message(top, text="This is the iCalGUI by Giavinh Lam. This app is compatible with iCalendar V2.0.")
	msg.pack(expand=YES, fill=BOTH)
	top.bind('<Escape>', lambda x:close(top))
	dismiss = Button(top, text="Okay", command=top.destroy)
	dismiss.pack()

def compDisplay(): #unnecessary now?
	componentString.set("NEW INFO")


def selectNode(event):
	global activenode
	global treeWidget
	global selectedNode
	if tv.focus():
		if activenode > 0 and event.widget == treeWidget and tv.focus() == selectedNode:
			selectedNode = tv.focus()
			root.focus()
			tv.selection_remove(selectedNode)
			activenode = 0
			showAlarm.place_forget()
			optionalProp.place_forget()

		elif event.widget == treeWidget:
			activenode = 1
			selectedNode = tv.focus()
			tv.selection_set(selectedNode)
			showAlarm.place(relx='.06', rely='.5', anchor="center")
			optionalProp.place(relx='.5', rely='.5', anchor="center")

def clear():
	logView.config(state=NORMAL)
	logView.delete('1.0', END)
	logView.insert(INSERT, "Log View Panel\n") #horizontal scroll bar??
	logView.config(state=DISABLED)

def displayAlarm():
	global printEA
	global EAStr
	global alarmString
	printEA = libc.printEventAlarms
	printEA.argtypes = [POINTER(Calendar)] #this can also be commented out
	printEA.restype = c_char_p      #this CANNOT be commented out! Otherwise Python will decide that printCal returns an int!

	item_iid = tv.selection()[0]
	EAStr = printEA(calPtr, makeCString(str(tv.item(item_iid)['text'])))
	logView.config(state=NORMAL)
	alarmString = EAStr.decode("utf-8")
	if alarmString.lower().find('action:') != -1:
		logView.insert(INSERT, EAStr.decode("utf-8"))
	else:
		logView.insert(INSERT, "Event has no alarms.\n")
	logView.see('end')
	logView.config(state=DISABLED)
'''
self.tree.item(idx)['text']
'''

def displayProp():
	printEP = libc.printEventProps
	#printEP.argtypes = [POINTER(Calendar)]
	printEP.restype = c_char_p
	item_iid = tv.selection()[0]
	EPStr = printEP(calPtr, makeCString(str(tv.item(item_iid)['text'])))
	logView.config(state=NORMAL)
	if EPStr.decode("utf-8").lower().count('\n') < 3:
		logView.insert(INSERT, "Event has no optional properties.\n")
	else:
		logView.insert(INSERT, EPStr.decode("utf-8"))

	logView.see('end')
	logView.config(state=DISABLED)

file = Menu(menubar, tearoff=0)	
file.add_command(label="Open (Ctrl-O)", command=fileOpen)
root.bind('<Control-o>', fileOpen)
file.add_command(label="Save (Ctrl-S)", command=saveFile)
root.bind('<Control-s>', saveFile)
file.add_command(label="Save as... (Shift-S)", command=saveasFile) #should make function for save as
root.bind('<Shift-S>', saveasFile)
file.add_command(label="Exit (Ctrl-X)", command=quit)
root.bind('<Control-x>', quit)
menubar.add_cascade(label="File", menu=file)

create = Menu(menubar, tearoff=0)
create.add_command(label="Create calendar", command=createCal)
create.add_command(label="Create event", command=createnewEvent)
create.entryconfig("Create event", state="disabled")
menubar.add_cascade(label="Create", menu=create)

help = Menu(menubar, tearoff=0)
help.add_command(label="About iCalGUI...", command=helpPopup)
menubar.add_cascade(label="Help", menu=help)

root.config(menu=menubar)

win = Frame(root)
win.pack(side=TOP, fill=BOTH)
win.place(anchor=NW, relwidth=1, relheight=0.4)

'''
fileView = Text(win)
fileView.pack(side=TOP, expand=YES)
fileView.insert(INSERT, "TEST3\n")

string = "EVENT1"
fileView.insert(END, string + "\n", string)
fileView.tag_configure(string, foreground="#0268E6", underline=TRUE)
fileView.tag_bind(string, "<1>", lambda event, :compDisplay())

fileView.config(state=DISABLED)
vscroll = Scrollbar(win, orient=VERTICAL, command=fileView.yview)
fileView['yscroll'] = vscroll.set
vscroll.pack(side="right", fill="y")
fileView.place(relwidth=1, relheight=1)
'''

tv = Treeview(win)
tv['columns'] = ('Props', 'Alarms', 'Summary')
tv.heading("#0", text='Event No.')
tv.column("#0", anchor='center', width=80)
tv.heading('Props', text='Props')
tv.column('Props', anchor='center', width=80)
tv.heading('Alarms', text='Alarms')
tv.column('Alarms', anchor='center', width=80)
tv.heading('Summary', text='Summary')
tv.column('Summary', anchor='w', width=500)

tv.place(relwidth=1, relheight=1)

vscroll = Scrollbar(win, orient=VERTICAL, command=tv.yview)
tv['yscroll'] = vscroll.set
vscroll.pack(side="right", fill="y")

root.bind("<Button-1>", selectNode)

treeWidget = tv

win2 = Frame(root)
win2.pack(side=BOTTOM, fill=BOTH)
win2.place(anchor=NW, relwidth=1, relheight=0.6, rely=0.4)

win3 = Frame(win2)
win3.pack(side=TOP, fill=BOTH)
win3.place(relwidth=1,relheight=0.15)

clear = Button(win3, text="Clear Log", command=clear)
clear.place(relx='.95', rely='.5', anchor="center")

showAlarm = Button(win3, text="Show Alarms", command=displayAlarm)
showAlarm.place_forget()

optionalProp = Button(win3, text="Extract Optional Props", command=displayProp)
optionalProp.place_forget()

logView = Text(win2)
logView.pack(side=BOTTOM, fill=X)
logView.insert(INSERT, "Log View Panel\n")
logView.config(state=DISABLED)
vscroll2 = Scrollbar(logView, orient=VERTICAL, command=logView.yview)
logView['yscroll'] = vscroll2.set
vscroll2.pack(side="right", fill="y")
logView.place(relwidth=1, relheight=0.85, rely=0.15)


root.protocol("WM_DELETE_WINDOW", closeVerify)
root.mainloop()


#A BETTER WAY
#from tkinter import *
#root = Tk()
#label(root, text='Hello GUI world!').pack(side=TOP)
#root.mainloop()

#bind or command for buttons and clicking
