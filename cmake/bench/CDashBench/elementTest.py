import xml.etree.ElementTree as ElementTree
import config

class ElementTest :

  def __init__(self, name, value, output="") :

    self._name = name.replace("<", "&lt;").replace(">", "&gt;")
    self._value = value.replace("<", "&lt;").replace(">", "&gt;")
    self._output = output

  # Retourne un element xml correspondant au test
  def getXmlElement(self) :
   
    xml = config.TEST_DESC_XML_STRING.format(self._name, self._value, self._output)

    # Creation de l'element representant le test
    return ElementTree.fromstring(xml)

  def name(self) :
    return self._name

  def getTestElement(self) :

    xml = config.TEST_ELEMENT_XML_STRING.format(self._name)

    return ElementTree.fromstring(xml)
