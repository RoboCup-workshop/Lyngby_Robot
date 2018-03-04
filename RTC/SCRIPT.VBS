Dim objFS, objFileTXT, objFileS2E, strPath, fullPatch,  strTemp, intPos, strNew, WshShell, fileName, ext_mBlock, strFind

'актуальное расширение файла расширения mBlock - вот такой вот каламбур))))
ext_mBlock = ".s2e"

'данное сочетание символов используется в тексте расширения для обозначения комментов которые нужно удалить
strFind="//_"

Set objArgs = WScript.Arguments
'полный путь с именем перетащенного на скрипт файла
fullPatch = objArgs(0)

Set objFS = CreateObject("Scripting.FileSystemObject")
'создание файла шаблона, для нахождения текущей директории при перетаскивании
CreateObject("Wscript.Shell").CurrentDirectory = Mid(Wscript.ScriptFullName, 1, InStrRev(Wscript.ScriptFullName, "\") - 1)

'текущая директория
Set WshShell = WScript.CreateObject("WScript.Shell")
strPath = WshShell.CurrentDirectory

'получаем название файла, перетащенного на скрипт
fileName = Replace(fullPatch,strPath & "\", "")

'проверяем текстовый ли файл перетащен на скрипт
if objFS.GetExtensionName(fullPatch)="txt" then
	'проверяем, если готовый файл расширения mBlock с расширением .s2e
	If not objFS.FileExists(Replace(fullPatch,".txt", ext_mBlock)) Then
		'открываем исходный файл для чтения, создаем файл с расширением .s2e для записи.
		Set objFileTXT = objFS.OpenTextFile(fullPatch)
		Set objFileS2E = objFS.CreateTextFile(Replace(fullPatch,".txt", ext_mBlock), True)
		
		'читаем исходный текстовик, пока не достигнем конца файла
		Do While Not objFileTXT.AtEndOfStream
			'читаем строчку
			strTemp = objFileTXT.ReadLine
			'находим позицию где начинается в строчке коммент
			intPos = InStr(1, strTemp, strFind, vbTextCompare)
			'если коммент есть, то....
			if intPos>0 then
				'формируем новую строку от начала строки, до начала коментариев (минус один, потомучто функция работает по указанный номер ВКЛЮЧИТЕЛЬНО"
				strNew = left(strTemp, intPos - 1)
				'пишем в новый файл измененную строку
				objFileS2E.Writeline strNew
			else
				'пишем в новый файл строку как есть (потому что комментов в ней нет)
				objFileS2E.Writeline strTemp
			end if
		loop
		'закрываем всё, работа сделана!
		objFileTXT.Close
		objFileS2E.Close
		WScript.Echo "Все операции выполнены успешно!"
	else
	WScript.Echo "Файл расширения с таким именем уже существует в текущей дирректории"
	end if
else
WScript.Echo "Используемый файл должен быть текстовым .txt"
end if

Set objFS = Nothing
WScript.Quit 0
