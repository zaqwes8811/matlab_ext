#-*- coding: utf-8 -*-
""" 
    file : import LabelFindEngine
    
    Функции поиска
    
    создает карту главных меток
    эталонная метка
    _xxx<:><;()/t< >;русские буквы>
    
    Форматирование можно сделать как callback
"""
import re

# own
from constants import *
from _label_purgers import purge_node
from _label_purgers import purge_line
from _label_purgers import purge_jamps_label

# нужно исключить табы и пробелы
_LABEL_PATTERN = '^\S.*?$'

def find_array_all_labels(code_lines):
    string = '\r\n'.join(code_lines)
    headers = list('')
    positions = list('')    # p^p^...^p на один диапазон меньше
    
    result = re.finditer(_LABEL_PATTERN , string, re.M | re.S | re.X)
    for match in result :
        # результаты поиска
        s = match.group()

        # Очистка результата и сохранение метки
        headers.append(purge_node(s))

        # и ее расположение
        pair = match.span()
        positions.append(pair[0])
  
    # добавляем конечную позицию
    # нужны... без них можно было обойтись и без рег.
    positions.append(len(string)-1)

    return headers, positions
    

def strContSubStrItTrue(string, substr):
    if string.find(substr) != -1:
        return True
    else:
        return False
"""
  заменяет фиктивными метками
  ret обходимы
  ret конечный 
  еще goto and bra
"""
def bypassAndRetFinder(string, j):
    splitString = string.split('\n')
    # нужно удалить комментарии
    resStr = list('')
    resInt = list()
    
    # очищаем от комментариев, очень важно, иначе прогр. реаг. на закомм. комм.
    # уже очищены
    splitStringPurge = splitString

    # обработка
    for i in range(len(splitStringPurge)):
        # Выделяем комманду вернее [0] здесь может быть все что угодно
        # Поиск входов-выходов и переходов
        lineSplited = splitStringPurge[i].split(';')
        if not 'bcf' in lineSplited[0]:    # bcxxxx Тоже подходит
            for at in markedJumps:    # пока только переходы с меткой
                patt = at+'.*?$'
                patt = unicode(patt, encoding='utf-8')
                result = re.finditer(patt , splitStringPurge[i], re.M | re.S | re.X)

                for match in result :
                    # результаты поиска
                    s = match.group()

                    # если был ретурн, то проверяем не обходимость
                    if strContSubStrItTrue(splitStringPurge[i], 'ret'): # есть ретурн
                        j = findedSpecialLabel(s, splitStringPurge[i-1], resStr, j, i, purge_line, 'ret')
                    elif strContSubStrItTrue(s, 'goto'): # если содержится mSlideTo то это фактически return в другом модуле
                        j = findedSpecialLabel(s, splitStringPurge[i-1], resStr, j, i, purge_jamps_label, '')
                    elif strContSubStrItTrue(s, 'bra'):     # Найдена комманда 'bra'
                        j = findedSpecialLabel(s, splitStringPurge[i-1], resStr, j, i, purge_jamps_label, '')
                    else :
                        #берем вторую часть комманду
                        resStr.append(purge_jamps_label(s))
                    # и ее расположение
                    pair = match.span()
                    resInt.append(pair[0])
    return resStr, j#, resInt
""" Функции поиска  """

""" Действия при нахождении специальной комманды """
def findedSpecialLabel(s, splitString, resStr, j, i, purgeFunction, type):
    s = purgeFunction(s)
    if type == 'ret':
        s += str(j)
    if bypassTest(splitString) == True and i > 0:
        resStr.append('xyz'+str(j))
        resStr.append(s)
    else :
        resStr.append('zxy'+str(j))
        resStr.append(s)
    j += 1
    return j

""" проверка не обходимость """
def bypassTest(firstCmd):
    for i in bypassCmds:
        result = re.finditer(i , firstCmd, re.M | re.S | re.X)
        for match in result :
            return True
    return False