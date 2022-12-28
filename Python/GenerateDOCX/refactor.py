# -*- coding : utf-8-*-
from docxtpl import DocxTemplate
import docx
import pandas as pd
import os
import csv
import numpy as np
from docx.oxml.ns import nsdecls
from docx.oxml import parse_xml
from docx import Document
from docx.shared import Pt
from docx.enum.text import WD_PARAGRAPH_ALIGNMENT


CURRENT_DIR = os.getcwd() + '/'  # 获取当前的路径
TEMPFILE = "情报要报.docx"
CSV_PATH = os.getcwd() + "/data/"
NEW_FILE_PATH = os.getcwd() + "/new/"


def move_table_after(table, paragraph):
    tbl, p = table._tbl, paragraph._p
    p.addnext(tbl)














