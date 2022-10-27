def ConvId(nombreartic):
    salida = ""

    for l in nombreartic:
        salida += str(ord(l))

    return int(salida)

def hashM(iduser,nombreartic, m):
    global prueba
    i = ConvId(nombreartic)
    prueba = int((i * iduser) % m)
    #return int(m * (i * 0.00000000000212324 % 1))
    return int((i * iduser) % m)

def agregar(iduser,nombreartic, ht, m):
    res = hashM(iduser,nombreartic, m)
    
    #ht[res].append(iduser)
    ht[res].append(prueba)



m = 13

ht = [ [] for i in range(m) ]

agregar(10, "andre", ht, m)
agregar(8,"luis", ht, m)
agregar(7,"andre1", ht, m)
agregar(5,"juan", ht, m)

for valor in ht:
    print("Valor: ", valor)

print(ht)