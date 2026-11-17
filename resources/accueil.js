function updateBars() {
    const bars = document.querySelectorAll('.bar'); // on sélectionne tous les éléments ayant la classe CSS 'bar'
    bars.forEach(bar => {  // pour chaque élément '.bar' on fait une boucle qui
        const value = parseInt(bar.getAttribute('data-value')); // on récupère la valeur de 'data-value' de l'élément '.bar' et la convertit en nombre entier
        const barFill = bar.querySelector('.bar-fill'); // on sélectionne l'élément child '.bar-fill' à l'intérieur de l'élément '.bar'
        const barLabel = bar.querySelector('.bar-label');  // on sélectionne l'élément child '.bar-label' à l'intérieur de l'élément '.bar'
        const barFillHeight = value * 3; //  // on calcule la hauteur de '.bar-fill' en multipliant la valeur (la value peut changer)
        barFill.style.height = `${barFillHeight}px`; // on applique la hauteur calculée à '.bar-fill'
        barLabel.textContent = barLabel.textContent.replace(/\s*\(\d+\)$/, ''); // on met à jour le texte de '.bar-label' pour inclure la valeur entre parenthèses
    });
}

function hasard() {
    // Filtrer les pages sans la page accueil.html
    const filteredPages = familyPages.filter(page => page !== "Accueil.html");
    // Sélectionner un index aléatoire dans le tableau filtré
    const randomIndex = Math.floor(Math.random() * filteredPages.length);
    // Obtenir la page aléatoire à partir du tableau filtré
    const randomPage = filteredPages[randomIndex];
    // Redirige vers la page séléctionné
    window.location.href = `../export/${randomPage}`;

}
function initialize() {
    updateBars();
}

function setupEventListeners() {
    document.querySelector('.help-button').addEventListener('click', hasard);
}

// Appeler les fonctions une fois le DOM chargé
initialize();
setupEventListeners();