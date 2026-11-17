
/* -------------------------------- Fenetre modale Mini jeu, bouton hasard, clic sur images  -------------------------------------*/

const script = document.createElement('script');
script.src = 'https://cdn.jsdelivr.net/npm/canvas-confetti@1.4.0/dist/confetti.browser.min.js'; //animation confettis
document.head.appendChild(script);



document.addEventListener('DOMContentLoaded', function() {

    let correctAnswers = 0; 
    let incorrectAnswers = 0;
    const maxCorrectAnswers = 6; //seuil maximum de bonne reponse avant la fin du jeu (gagner)
    const maxIncorrectAnswers = 3; //seuil maximum de mauvaise réponses avant le perdre

    /* info Personne recherchée */
    const nom = document.getElementById("nom").textContent.trim();
    const prenom = document.getElementById("prenom").textContent.trim();
    const birthday = document.getElementById("birthday").textContent.trim();
    const region = document.getElementById("region").textContent.trim();

    /* info Mère */
    const nomM = document.getElementById("nomM").textContent.trim();
    const prenomM = document.getElementById("prenomM").textContent.trim();
    const birthdayM = document.getElementById("birthdayM").textContent.trim();
    const regionM = document.getElementById("regionM").textContent.trim();

    /* info Père */
    const nomP = document.getElementById("nomP").textContent.trim();
    const prenomP = document.getElementById("prenomP").textContent.trim();
    const birthdayP = document.getElementById("birthdayP").textContent.trim();
    const regionP = document.getElementById("regionP").textContent.trim();

    /* info Grand-père paternel */
    const nomGPP = document.getElementById("nomGPP").textContent.trim();
    const prenomGPP = document.getElementById("prenomGPP").textContent.trim();
    const birthdayGPP = document.getElementById("birthdayGPP").textContent.trim();
    const regionGPP = document.getElementById("regionGPP").textContent.trim();

    /* info Grand-mère paternelle */
    const nomGMP = document.getElementById("nomGMP").textContent.trim();
    const prenomGMP = document.getElementById("prenomGMP").textContent.trim();
    const birthdayGMP = document.getElementById("birthdayGMP").textContent.trim();
    const regionGMP = document.getElementById("regionGMP").textContent.trim();

    /* info Grand-père maternel */
    const nomGPM = document.getElementById("nomGPM").textContent.trim();
    const prenomGPM = document.getElementById("prenomGPM").textContent.trim();
    const birthdayGPM = document.getElementById("birthdayGPM").textContent.trim();
    const regionGPM = document.getElementById("regionGPM").textContent.trim();

    /* info Grand-mère maternelle */
    const nomGMM = document.getElementById("nomGMM").textContent.trim();
    const prenomGMM = document.getElementById("prenomGMM").textContent.trim();
    const birthdayGMM = document.getElementById("birthdayGMM").textContent.trim();
    const regionGMM = document.getElementById("regionGMM").textContent.trim();

    const questions =[
        //enfant
        {question: 'Quel est le nom de cet enfant ?', answer: nom},
        {question: 'Quel est le prénom de cet enfant ?', answer: prenom},
        {question:'Quand est né(e) cet enfant ?', answer: birthday},
        {question: 'Où est né(e) cet enfant ?', answer: region},
        //mère
        {question: 'Quel est le nom de la mère ?', answer: nomM},
        {question: 'Quel est le prénom de la mère ?', answer: prenomM},
        {question:'Quand est née la mère ?', answer: birthdayM},
        {question: 'Où est née la mère ?', answer: regionM}, 
        //père
        {question: 'Quel est le nom du père ?', answer: nomP},
        {question: 'Quel est le prénom du père ?', answer: prenomP},
        {question:'Quand est né le père ?', answer: birthdayP},
        {question: 'Où est né le père ?', answer: regionP},
        //grand père paternel
        {question: 'Quel est le nom du grand père paternel ?', answer: nomGPP},
        {question: 'Quel est le prénom du grand père paternel ?', answer: prenomGPP},
        {question:'Quand est né le grand père paternel ?', answer: birthdayGPP},
        {question: 'Où est né le grand père paternel ?', answer: regionGPP},
        //grand mère paternel
        {question: 'Quel est le nom de la grand mère paternel ?', answer: nomGMP},
        {question: 'Quel est le prénom de la grand mère paternel ?', answer: prenomGMP},
        {question:'Quand est née la grand mère paternel ?', answer: birthdayGMP},
        {question: 'Où est née la grand mère paternel ?', answer: regionGMP},
        //grand père maternel
        {question: 'Quel est le nom du grand père maternel ?', answer: nomGPM},
        {question: 'Quel est le prénom du grand père maternel ?', answer: prenomGPM},
        {question:'Quand est né le grand père maternel ?', answer: birthdayGPM},
        {question: 'Où est né le grand père maternel ?', answer: regionGPM},
        //grand mère maternel
        {question: 'Quel est le nom de la grand mère maternel ?', answer: nomGMM},
        {question: 'Quel est le prénom de la grand mère maternel ?', answer: prenomGMM},
        {question:'Quand est née la grand mère maternel ?', answer: birthdayGMM},
        {question: 'Où est née la grand mère maternel ?', answer: regionGMM} 
    ];


    function getRandomQuestion() {
        //cette fonction selectionne aléatoirement une question parmis celles dans le tableau 'questions'
        const randomIndex = Math.floor(Math.random() * questions.length);
        return questions[randomIndex];
    }


    function createModal(title, questionObj) {
        const modal = document.createElement('div'); // Crée un div pour la modale
        modal.classList.add('modal', 'show'); // Ajoute la classe 'modal' au div

        const modalContent = document.createElement('div'); // Crée un div pour le contenu de la modale
        modalContent.classList.add('modal-content'); // Ajoute la classe 'modal-content'

        const closeModal = document.createElement('span'); // Crée un élément span pour fermer la modale
        closeModal.classList.add('close'); // Ajoute la classe 'close'
        closeModal.innerHTML = '&times;'; // Définit le contenu HTML pour afficher un 'x'
        closeModal.addEventListener('click', function () {
            modal.classList.remove('show'); // Ajoute un événement pour fermer la modale quand on clique sur le 'x'
        });

        
        closeModal.addEventListener("mouseover", function() {
            // Changez la couleur du texte en rouge lorsque survolé
            closeModal.style.color = "red";
        });
        
        // Ajoutez un écouteur d'événement pour détecter lorsque la souris quitte l'élément
        closeModal.addEventListener("mouseout", function() {
            // Rétablissez la couleur initiale (ou toute autre logique de style souhaitée)
            closeModal.style.color = ""; // Cela réinitialise à la valeur par défaut définie dans votre CSS
        });




        const modalTitle = document.createElement('h2');//crée un titre h2 pour la modale
        modalTitle.textContent = title;//définit un texte du titre dan la modale


        const modalSubtitle = document.createElement('p');
        modalSubtitle.textContent = "Vous devez répondre à 6 questions correctement pour terminer le jeu. Attention vous n'avez que 3 vies.";
        
        const modalSubtitle2 = document.createElement('p');
        modalSubtitle2.textContent = "S'il n'y a pas de réponse entrer \'inconnu\.'";

        

        const modalText = document.createElement('p');//crée un paragraphe pour le texte de la question
        modalText.textContent = questionObj.question;//définit le texte de la question dans le paragraphe 




        // Zone de texte pour répondre
        const inputField = document.createElement('input');// Crée un champ de saisie pour la réponse
        inputField.type = 'text';// Définit le type de champ comme texte
        inputField.placeholder = 'Votre réponse...'; // Définit le texte de placeholder
        inputField.style.width = '80%';// Définit la largeur du champ de saisie
        inputField.style.margin = '10px 0';// Définit les marges du champ de saisie
        inputField.style.padding = '10px'; // style du champ de saisie
        inputField.style.fontSize = '16px';// Définit la taille de la police du champ de saisie


        const submitButton = document.createElement('button');// Crée un bouton de soumission
        submitButton.textContent = 'Vérifier';// Définit le texte du bouton
        submitButton.style.padding = '10px 20px';
        submitButton.style.fontSize = '16px';// Définit la taille de la police du bouton
        
        submitButton.addEventListener('click', function () {
            const userAnswer = inputField.value.trim().toLowerCase();// Récupère la réponse de l'utilisateur, en minuscules et sans espaces inutiles
            const correctAnswer = questionObj.answer.toLowerCase();// Récupère la réponse correcte attendue, en minuscules

            if (userAnswer === correctAnswer) {// Vérifie si la réponse de l'utilisateur est correcte
                alert('Bonne réponse !');
                correctAnswers++;// Incrémente le compteur de bonnes réponses

                

            } 
            else {
                alert('Mauvaise réponse. La réponse correcte est : ' + correctAnswer);
                incorrectAnswers++;// Incrémente le compteur de mauvaises réponses
                console.log("Mauvaise réponse, -1 essai");
            }
            modal.classList.remove('show');// Ferme la modale en retirant la classe 'show'


            if (correctAnswers >= maxCorrectAnswers) {// Vérifie si le nombre maximum de bonnes réponses a été atteint
                alert('Félicitations, vous avez gagné !');        
                confetti({//lance les confettis
                    particleCount: 100,
                    spread: 70,
                    origin: { y: 0.6 }
                });
                resetGame(); //reinitialise le jeu


            } 
            else if (incorrectAnswers >= maxIncorrectAnswers) {// Vérifie si le nombre maximum de mauvaises réponses a été atteint
                alert('Désolé, vous avez perdu.');
                resetGame();//reinitialise le jeu
            } 
            else {
                askRandomQuestion();// Pose une nouvelle question aléatoire
            }

        });


        // Texte indiquant le nombre de questions et d'erreurs
        const questionsInfo = document.createElement('p');
        questionsInfo.textContent = `Questions faites : ${correctAnswers + incorrectAnswers} | Réponses correctes : ${correctAnswers} / 6 | Erreurs : ${incorrectAnswers} / 3 `;
        questionsInfo.style.marginTop = '50px';


        modalContent.appendChild(closeModal); // Ajoute le bouton de fermeture au contenu de la modale
        modalContent.appendChild(modalTitle); // Ajoute le titre de la modale au contenu de la modale
        modalContent.appendChild(modalSubtitle); // Ajoute le sous-titre à la modale
        modalContent.appendChild(modalSubtitle2); // Ajoute le sous-titre à la modale

        modalContent.appendChild(modalText); // Ajoute le texte de la question au contenu de la modale
        modalContent.appendChild(inputField); // Ajoute le champ de saisie au contenu de la modale
        modalContent.appendChild(submitButton); // Ajoute le bouton de soumission au contenu de la modale
        
        modalContent.appendChild(questionsInfo); // Ajoute les informations sur les questions et erreurs

        
        modal.appendChild(modalContent); // Ajoute le contenu de la modale à la modale elle-même
        

        document.body.appendChild(modal); // Ajoute la modale au corps du document
    }


    function askRandomQuestion() {
        const randomQuestion = getRandomQuestion();// Sélectionne une question aléatoire
        createModal('Mini jeu', randomQuestion);// Crée une modale avec le titre 'Mini jeu' et la question sélectionnée
    }
    

    function resetGame() {
        correctAnswers = 0; //réinitiaise le compteur de bonnes réponses 
        incorrectAnswers = 0;//réinitiaise le compteur de mauvaises réponses 
    }

    function addTitleClickEvents() {
        const miniGameText = document.querySelector('.mini-game-text');// Sélectionne l'élément avec la classe 'mini-game-text'
        
        if (miniGameText) { // Vérifie si l'élément avec la classe 'mini-game-text' existe
            miniGameText.addEventListener('click', function () {// Ajoute un événement de clic à cet élément
                askRandomQuestion();// Lorsque l'élément est cliqué, pose une nouvelle question aléatoire
            });
        }
    }


    addTitleClickEvents();// Appelle la fonction pour ajouter l'événement de clic à l'élément avec la classe 'mini-game-text'


        

});

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


function navigateToPerson(element) {
    // on prend la valeur de'data-id'
    const personId = element.getAttribute('data-id');
    //on vérifie si personId contient une valeur
    if (personId) {
        // on redirige l'utilisateur vers la page HTML correspondant à l'ID de la personne
        window.location.href = `../export/${personId}.html`;
    } else {
        alert("ID de personne non valide.");
    }
}


function backBoutton() {
    window.location.href = 'accueil.html'; // Redirige vers la page d'accueil
}



