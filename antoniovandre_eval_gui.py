# Proprietário: Antonio Vandré Pedrosa Furtunato Gomes (bit.ly/antoniovandre_legadoontologico).

# GUI para "antoniovandre_eval", versão de distribuição.

# Última atualização: 12-07-2020.

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

	lbl_saida.configure (text=string)

	os.system ('rm avevtemp')

def clicked2 ():

	cmd = 'gedit /usr/share/antoniovandre_sobre.txt'

	os.system (cmd)

def clicked3 ():

	quit ()

btn_calcular = Button(window, text="Calcular", command=clicked)

btn_calcular.place(anchor='center', relx=.3, rely=.5)

btn_ajuda = Button(window, text="Ajuda", command=clicked2)

btn_ajuda.place(anchor='center', relx=.5, rely=.5)

btn_exit = Button(window, text="Sair", command=clicked3)

btn_exit.place(anchor='center', relx=.7, rely=.5)

window.mainloop()

