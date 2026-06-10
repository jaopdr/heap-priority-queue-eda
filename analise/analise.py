import numpy as np
import matplotlib.pyplot as plt
import csv

ns     = []
medias = []

with open("../resultados/resultados.csv", "r") as f:
    reader = csv.DictReader(f)
    for row in reader:
        ns.append(int(row["n"]))
        medias.append(float(row["media_iteracoes"]))

ns     = np.array(ns)
medias = np.array(medias)

log_ns = np.log2(ns)

coef = np.polyfit(log_ns, medias, 1)
a, b = coef
print(f"Curva ajustada: media ≈ {a:.4f} * log2(n) + {b:.4f}")

ns_smooth     = np.linspace(ns.min(), ns.max(), 500)
medias_smooth = a * np.log2(ns_smooth) + b

fig, axes = plt.subplots(1, 2, figsize=(14, 5))
fig.suptitle("Heap Priority Queue – Média de Iterações de Heapify por Inserção",
             fontsize=13, fontweight="bold")

ax1 = axes[0]
ax1.scatter(ns, medias, color="steelblue", zorder=5, label="Dados medidos")
ax1.plot(ns_smooth, medias_smooth, color="tomato", linewidth=2,
         label=f"Ajuste: {a:.3f}·log₂(n) + {b:.3f}")
ax1.set_xlabel("Tamanho da base (n)")
ax1.set_ylabel("Média de iterações")
ax1.set_title("Escala linear")
ax1.legend()
ax1.grid(True, linestyle="--", alpha=0.5)

ax2 = axes[1]
ax2.scatter(log_ns, medias, color="steelblue", zorder=5, label="Dados medidos")
ax2.plot(log_ns, a * log_ns + b, color="tomato", linewidth=2,
         label="Ajuste linear (confirma O(log n))")
ax2.set_xlabel("log₂(n)")
ax2.set_ylabel("Média de iterações")
ax2.set_title("Eixo X em log₂(n)  –  linha reta = O(log n) confirmado")
ax2.legend()
ax2.grid(True, linestyle="--", alpha=0.5)

plt.tight_layout()
plt.savefig("grafico_heap.png", dpi=150)
plt.show()
print("Gráfico salvo em 'grafico_heap.png'.")

print("\n===== ANÁLISE DOS RESULTADOS =====")
print(f"  Menor média  : {medias.min():.4f}  (n = {ns[medias.argmin()]})")
print(f"  Maior média  : {medias.max():.4f}  (n = {ns[medias.argmax()]})")
print(f"  Coeficiente a: {a:.4f}  (inclinação da curva log)")
print(f"  Coeficiente b: {b:.4f}  (intercepto)")
print()
print("  A inserção numa Max-Heap tem complexidade O(log n) no pior caso.")
print("  Se a média de iterações cresce de forma logarítmica com n,")
print("  os resultados confirmam o que a literatura descreve.")
print()

residuos  = medias - (a * log_ns + b)
ss_res    = np.sum(residuos ** 2)
ss_tot    = np.sum((medias - medias.mean()) ** 2)
r2        = 1 - ss_res / ss_tot
print(f"  R² do ajuste logarítmico: {r2:.4f}")
if r2 > 0.90:
    print("  → Ajuste EXCELENTE: os dados seguem fortemente O(log n).")
elif r2 > 0.70:
    print("  → Ajuste BOM: os dados seguem razoavelmente O(log n).")
else:
    print("  → Ajuste FRACO: pode haver ruído ou outro fator influenciando.")