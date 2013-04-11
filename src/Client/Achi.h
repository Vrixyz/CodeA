#ifndef ACHI_H
#define ACHI_H

struct achiv
{
    std::string name;
    std::string describe;
};

struct achiv achivClass[25] =
{
    {"Salade de phalanges", "Infligez plus de 50pts de degats en une seule partie."},
    {"Vite ! Le DPR arrive !", "Gagner une partie en moins de 30 sec."},
    {"Hmm... Gagne d'avance !", "Gagner une partie qui a duree plus de 10minutes."},
    {"Shields, shields everywhere !", "En tant que Mage, invoquer au moins 10 portails durant une partie."},
    {"Les renforts sont la !", "En tant qu'Invocateur, invoquer au moins 25 sbires durant une partie."},
    {"Apprenti Prestidigitateur", "Jouer 1 partie en tant qu'Invocateur."},
    {"Apprenti Illusioniste", "Jouer 25 parties en tant qu'Invocateur."},
    {"Apprenti Invocateur", "Jouer 100 parties en tant qu'Invocateur."},
    {"Apprenti Ensorceleur", "Jouer 250 parties en tant qu'Invocateur."},
    {"Apprenti Maitre des Illusions", "Jouer 1000 parties en tant qu'Invocateur."},
    {"Prestidigitateur", "Gagner 1 partie en tant qu'Invocateur."},
    {"Illusioniste", "Gagner 25 parties en tant qu'Invocateur."},
    {"Invocateur", "Gagner 100 parties en tant qu'Invocateur."},
    {"Ensorceleur", "Gagner 250 parties en tant qu'Invocateur."},
    {"Maitre des Illusions", "Gagner 1000 parties en tant qu'Invocateur."},
    {"Apprenti Magicien", "Jouer 1 partie en tant que Mage."},
    {"Apprenti Mage", "Jouer 25 parties en tant que Mage."},
    {"Apprenti Mage de Guerre", "Jouer 100 parties en tant que Mage."},
    {"Apprenti Maitre Mage", "Jouer 250 parties en tant que Mage."},
    {"Apprenti Archimage", "Jouer 1000 parties en tant que Mage."},
    {"Magicien", "Gagner 1 partie en tant que Mage."},
    {"Mage", "Gagner 25 parties en tant que Mage."},
    {"Mage de Guerre", "Gagner 100 parties en tant que Mage."},
    {"Maitre Mage", "Gagner 250 parties en tant que Mage."},
    {"Archimage", "Gagner 1000 parties en tant que Mage."},
};

struct achiv achivDivers[20] =
{
    {"Apprenti Soldat", "Jouer 1 partie."},
    {"Apprenti Caporal", "Jouer 25 parties."},
    {"Apprenti Sergent", "Jouer 100 parties."},
    {"Apprenti Chevalier", "Jouer 250 parties."},
    {"Apprenti Commandant", "Jouer 1000 parties."},
    {"Soldat", "Gagner 1 partie."},
    {"Caporal", "Gagner 25 parties."},
    {"Sergent", "Gagner 100 parties."},
    {"Chevalier", "Gagner 250 parties."},
    {"Commandant", "Gagner 1000 parties."},
    {"Apprenti Touche a Tout", "Jouer 1 partie avec chaque classe."},
    {"Apprenti Tacticien", "Jouer 25 parties avec chaque classe."},
    {"Apprenti Genie", "Jouer 100 parties avec chaque classe."},
    {"Apprenti Prodige", "Jouer 250 parties avec chaque classe."},
    {"Apprenti Maitre de Guerre", "Jouer 1000 parties avec chaque classe."},
    {"Touche a Tout", "Gagner 1 partie avec chaque classe."},
    {"Tacticien", "Gagner 25 parties avec chaque classe.."},
    {"Genie", "Gagner 100 parties avec chaque classe.."},
    {"Prodige", "Gagner 250 parties avec chaque classe.."},
    {"Maitre de Guerre", "Gagner 1000 parties avec chaque classe.."},
};

#endif // ACHI_H
