GXX=g++
CXXFLAGS=-std=c++14
PROGRAM=gilmore

all: main.o gilmore_procedure.o herbrand_universe.o forall.o exists.o quantifier.o iff.o imp.o or.o and.o binaryconnective.o not.o unaryconnective.o constants.o atom.o atomicformula.o baseformula.o functionterm.o variableterm.o baseterm.o lstructure.o signature.o valuation.o domain.o
	$(GXX) $(CXXFLAGS) $^ -o $(PROGRAM)

main.o: main.cpp first_order_logic.h herbrand_universe.h gilmore_procedure.h
	$(GXX) $(CXXFLAGS) -c $< -o $@

gilmore_procedure.o: gilmore_procedure.cpp first_order_logic.h herbrand_universe.h gilmore_procedure.h
	$(GXX) $(CXXFLAGS) -c $< -o $@

herbrand_universe.o: herbrand_universe.cpp first_order_logic.h utils.h herbrand_universe.h
	$(GXX) $(CXXFLAGS) -c $< -o $@

forall.o: forall.cpp first_order_logic.h quantifier.h forall.h
	$(GXX) $(CXXFLAGS) -c $< -o $@

exists.o: exists.cpp first_order_logic.h quantifier.h exists.h
	$(GXX) $(CXXFLAGS) -c $< -o $@

quantifier.o: quantifier.cpp variableterm.h common.h baseformula.h quantifier.h
	$(GXX) $(CXXFLAGS) -c $< -o $@

iff.o: iff.cpp binaryconnective.h first_order_logic.h iff.h
	$(GXX) $(CXXFLAGS) -c $< -o $@

imp.o: imp.cpp binaryconnective.h first_order_logic.h imp.h
	$(GXX) $(CXXFLAGS) -c $< -o $@

or.o: or.cpp binaryconnective.h first_order_logic.h or.h
	$(GXX) $(CXXFLAGS) -c $< -o $@

and.o: and.cpp binaryconnective.h first_order_logic.h and.h
	$(GXX) $(CXXFLAGS) -c $< -o $@

binaryconnective.o: binaryconnective.cpp baseformula.h binaryconnective.h
	$(GXX) $(CXXFLAGS) -c $< -o $@

not.o: not.cpp unaryconnective.h first_order_logic.h not.h
	$(GXX) $(CXXFLAGS) -c $< -o $@

unaryconnective.o: unaryconnective.cpp baseformula.h unaryconnective.h
	$(GXX) $(CXXFLAGS) -c $< -o $@

constants.o: constants.cpp atomicformula.h constants.h
	$(GXX) $(CXXFLAGS) -c $< -o $@

atom.o: atom.cpp atomicformula.h baseterm.h signature.h lstructure.h atom.h
	$(GXX) $(CXXFLAGS) -c $< -o $@

atomicformula.o: atomicformula.cpp baseformula.h common.h atomicformula.h
	$(GXX) $(CXXFLAGS) -c $< -o $@

baseformula.o: baseformula.cpp baseterm.h lstructure.h common.h valuation.h first_order_logic.h baseformula.h
	$(GXX) $(CXXFLAGS) -c $< -o $@

functionterm.o: functionterm.cpp baseterm.h signature.h functionterm.h
	$(GXX) $(CXXFLAGS) -c $< -o $@

variableterm.o: variableterm.cpp baseterm.h variableterm.h
	$(GXX) $(CXXFLAGS) -c $< -o $@

baseterm.o: baseterm.cpp common.h valuation.h lstructure.h baseterm.h
	$(GXX) $(CXXFLAGS) -c $< -o $@

lstructure.o: lstructure.cpp domain.h common.h signature.h lstructure.h
	$(GXX) $(CXXFLAGS) -c $< -o $@ 

signature.o: signature.cpp common.h signature.h
	$(GXX) $(CXXFLAGS) -c $< -o $@

valuation.o: valuation.cpp domain.h valuation.h
	$(GXX) $(CXXFLAGS) -c $< -o $@

domain.o: domain.cpp common.h domain.h
	$(GXX) $(CXXFLAGS) -c $< -o $@


.PHONY: clean

clean:
	rm -rf *.o $(PROGRAM) *~
