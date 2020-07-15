# Proprietário: Antonio Vandré Pedrosa Furtunato Gomes (bit.ly/antoniovandre_legadoontologico).

# GUI para "antoniovandre_eval", versão de distribuição.

# Última atualização: 15-07-2020.

import tkinter as tk

from tkinter import *

import os

window = Tk ()

window.geometry('410x150')

window.resizable (False, False)

bgimage = PhotoImage (file="/usr/share/antoniovandre_eval_gui_bgimage.png")

bglabel = Label (window, image=bgimage)

bglabel.place (x=0, y=0, relwidth=1, relheight=1)

window.title ("antoniovandre_eval GUI")

lbl_entre = Label (window, text="Entre com a expressão:")

lbl_entre.place (anchor='w', rely=.1)

txt = Entry (window, width=50)

txt.place (anchor='w', rely=.3)

lbl_resultado = Label (window, text="Resultado:")

lbl_resultado.place (anchor='w', rely=.7)

lbl_saida = Label (window, text="Entre com uma expressão e clique no botão para calcular.")

lbl_saida.place (anchor='w', rely=.9)

def clicked ():

	cmd = 'antoniovandre_eval \'' + txt.get() + '\' > avevtemp'

	os.system (cmd)

	with open ("avevtemp", "r") as f:
		string = f.read ()

	lbl_saida.configure (text=string.rstrip("\n"))

	os.system ('rm avevtemp')

def clicked2 ():

	with open ("/usr/share/antoniovandre_sobre.txt", "r") as fa:
		stringajuda = fa.read ()

	windowajuda = Tk ()

	windowajuda.resizable (False, False)

	windowajuda.title ("antoniovandre_eval GUI ajuda")

	S = tk.Scrollbar (windowajuda)

	T = tk.Text (windowajuda, height=30, width=100)

	S.pack (side=tk.RIGHT, fill=tk.Y)

	T.pack (side=tk.LEFT, fill=tk.Y)

	S.config (command=T.yview)

	T.config (yscrollcommand=S.set)

	T.insert (tk.INSERT, stringajuda)

	windowajuda.mainloop ()

def clicked3 ():

	quit ()

btn_calcular = Button (window, text="Calcular", command=clicked)

btn_calcular.place (anchor='center', relx=.3, rely=.5)

btn_ajuda = Button (window, text="Ajuda", command=clicked2)

btn_ajuda.place (anchor='center', relx=.5, rely=.5)

btn_exit = Button (window, text="Sair", command=clicked3)

btn_exit.place (anchor='center', relx=.7, rely=.5)

window.mainloop ()

