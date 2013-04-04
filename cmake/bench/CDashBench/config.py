BENCH                   = "[Benchmark]"

# Flag pour reperer si le test est un benchmark
BENCH_FLAG              = "(\[.*\][ ]?)+"

BENCH_FIELD             = {"name" : 0, "size" : 1, "value" : 2, "unit" : 3}

# Nom utilise pour la creation des bench
# {0} nom du test unitaire generant le bench
# {1} grandeur caracteristique
# {2} Unite
BENCH_NAME              = "{0}({1})_{2}"

# Element XML pour l'ajout et le recherche dans le document XML
TESTS_ROOT_ELEMENT_NAME = "Testing"
TEST_ELEMENT_NAME       = "Test"
OUTPUT_ELEMENT_NAME     = "Results/Measurement/Value"
TESTLIST_ELEMENT_NAME   = "TestList"

# XML correspondant a un sous element Test de TestLib
TEST_ELEMENT_XML_STRING = "<Test>./{0}</Test>"

# XML permettant de creer un noueau test
TEST_DESC_XML_STRING    = """
<Test Status="passed">
  <Name>{0}</Name>
  <Path>.</Path>
  <FullName>./{0}</FullName>
  <FullCommandLine>CDASHBENCH</FullCommandLine>
  <Results>
    <NamedMeasurement type="numeric/double" name="Execution Time">
      <Value>{1}</Value>
    </NamedMeasurement>
    <NamedMeasurement type="text/string" name="Completion Status">
      <Value>Completed</Value>
    </NamedMeasurement>
    <NamedMeasurement type="text/string" name="Command Line">
      <Value>CDASHBENCH</Value>
    </NamedMeasurement>
    <Measurement>
      <Value>{2}</Value>
    </Measurement>
  </Results>
</Test>
"""

VS_TEMPLATE_OUTPUT     = ["struct", "class"]
