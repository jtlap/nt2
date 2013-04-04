import xml.etree.ElementTree as ElementTree
from elementTest import *
import re
import os, sys
import config
import cStringIO

def cleanStr(str) :
  return " ".join(str.strip().split())

# Permet de parser la sortie des tests unitaires afin de recuperer 
# les benchmark qu'il peut y avoir
def parseOutput(testName, content, compression) :

  elements = []

  # Si la sortie du test a ete compressee on la decompresse
  if compression == True :
    content = content.decode('base64').decode('zlib')

  output = cStringIO.StringIO(content)
  
  # Liste contenant les elements xml a ajouter au xml global
  line = cleanStr(output.readline())
    
  # La sortie du bench a matche avec ce que l'on cherche
  if re.match(config.BENCH_FLAG, line) :
   
    # Pour toutes les lignes de la sortie
    for bench in output :
     
      if bench[0] != '-' :
        values = cleanStr(bench).split()
        
        # Si la sortie est formattee par Visual studio on supprime le class ou le struct
        if values[config.BENCH_FIELD["name"]] in config.VS_TEMPLATE_OUTPUT :
          values = values[1:]

        # Si la ligne match sur une sortie de benchmark
        if values :
          try :
            elements.append(ElementTest(config.BENCH_NAME.format(values[config.BENCH_FIELD["name"]], values[config.BENCH_FIELD["size"]], values[config.BENCH_FIELD["unit"]]), values[config.BENCH_FIELD["value"]]))
          except :
            pass

  return elements
  
# Lance le parsing des sorties sur tous les tests trouves dans le fichier xml
def processing(path) :

  root = ElementTree.parse(path)

  testingElement = root.find(config.TESTS_ROOT_ELEMENT_NAME)

  # Recuperation des tests du fichier xml courant
  tests = testingElement.findall(config.TEST_ELEMENT_NAME)
  testList = testingElement.find(config.TESTLIST_ELEMENT_NAME)

  # Recuperation de la sortie des tests pour les parser
  for test in tests :
    outputElement = test.find(config.OUTPUT_ELEMENT_NAME)
    gzip = True

    # Si la sortie est compressee
    try :
      outputElement.attrib['compression'] 
    except :
      gzip = False
    
    elements = parseOutput(test.find("Name").text, outputElement.text, gzip)
    
    for element in elements :

      # Ajout du nouveau test dans le liste des tests du fichier XML (tag TESTLIST_ELEMENT_NAME)
      testList.append(element.getTestElement())

      # Ajout d'un element XML correspondant au nouveau test
      testingElement.append(element.getXmlElement())

    if elements :
      # Suppression du test unitaire ayant permis de creer les benchmark
      testingElement.remove(test)

  root.write(path)

if __name__ == "__main__":
  
  if len(sys.argv) == 2 :
    processing(sys.argv[1])
  else :
    print "Usage : python bench.py file.xml"

