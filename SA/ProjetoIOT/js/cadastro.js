let contador = 3;

function adicionar() {
  const container = document.getElementById("freezerContainer");

  const novo = document.createElement("div");
  novo.classList.add("card");
  novo.innerText = "freezer " + contador;

  novo.onclick = function () {
    editar(novo);
  };

  // adiciona antes do botão +
  container.insertBefore(novo, container.lastElementChild);

  contador++;
}

function editar(elemento) {
  let novoNome = prompt("Digite o novo nome do freezer:");

  if (novoNome !== null && novoNome !== "") {
    elemento.innerText = novoNome;
  }
}