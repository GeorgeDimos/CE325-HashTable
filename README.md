# Πίνακας Κατακερματισμού (HashTable)

Υλοποιείται η αποθήκευση λέξεων (δηλ. αλφαριθμητικών που δεν περιέχουν κενά) σε ένα πίνακα κατακερματισμού ( HashTable ). Οι πίνακες κατακερματισμού χρησιμοποιούνται για την γρήγορη ένθεση, αναζήτηση και διαγραφή στοιχείων μέσα σε αυτούς. Το μειονέκτημα των πινάκων κατακερματισμού είναι ότι κατά κανόνα χρησιμοποιούν περισσότερο χώρο από όσο πραγματικά χρειάζονται, πράγμα που τους καθιστά ακατάλληλους για μεγάλο όγκο δεδομένων.
### Ένθεση στον πίνακα κατακερματισμού
Η θέση ένθεσης ενός στοιχείου στον πίνακα κατακερματισμού δίνεται από την συνάρτηση κατακερματισμού η οποία συνοψίζεται στα εξής:

> ![](https://latex.codecogs.com/gif.latex?h_%7Bn%7D%28x%29%20%3D%20%28x&plus;n%29%5C%20modulo%5C%20TABLE%5C_SIZE)

δηλαδή ![](https://latex.codecogs.com/gif.latex?h_%7B0%7D%28x%29%20%3D%20h%28x%29%2C%5C%20h_%7B1%7D%28x%29%20%3D%20h%28x&plus;1%29%2C%5C%20h_%7B2%7D%28x%29%20%3D%20h%28x&plus;2%29) κ.ο.κ., όπου x είναι το άθροισμα των ASCII κωδικών των χαρακτήρων κάθε περιεχόμενης λέξης.

Αρχικά η συνάρτηση κατακερματισμού επιχειρεί να εισάγει το νέο στοιχείο στην θέση που προκύπτει από την παραπάνω σχέση για n=0. Εάν η θέση είναι διαθέσιμη τότε το στοιχείο εισάγεται στην θέση αυτή. Εάν η θέση δεν είναι διαθέσιμη τότε προχωρά στην εξέταση της επόμενης θέσης προς ένθεση που δίνει η συνάρτηση κατακερματισμού για n=1. Εάν η νέα θέση είναι διαθέσιμη τότε το στοιχείο εισάγεται στην θέση αυτή, ενώ εάν δεν είναι διαθέσιμη προχωρά στην επόμενη θέση. Η διαδικασία συνεχίζεται μέχρι να βρούμε διαθέσιμη θέση ή μέχρι να επιστρέψουμε στην αρχική θέση που μας επέστρεψε η συνάρτηση κατακερματισμού για n=0 .

Με βάση την συνάρτηση κατακερματισμού αναζητούμε την 1η διαθέσιμη προς ένθεση θέση. Μία διαθέσιμη θέση ορίζεται ως μία θέση που είτε δεν έχει αποθηκευτεί κανένα στοιχείο κατά το παρελθόν, είτε έχει αποθηκευτεί κάποιο στοιχείο, αλλά πλέον έχει διαγραφεί.
1. Εάν δεν έχει αποθηκευτεί κανένα στοιχείο κατά το παρελθόν τότε αντικείμενο τύπου string στην αντίστοιχη θέση είναι κενό.
2. Εάν έχει αποθηκευτεί κάποιο στοιχείο κατά το παρελθόν και στη συνέχεια έχει διαγραφεί, τότε το αντικείμενο string στην αντίστοιχη θέση έχει το περιεχόμενο “##tomb##” (από τα αρχικά της λέξης tombstone).

### Αναζήτηση στον πίνακα κατακερματισμού
Η αναζήτηση στον πίνακα κατακερματισμού χρησιμοποιεί τη συνάρτηση κατακερματισμού για να εντοπίσει εάν υπάρχει το στοιχείο προς αναζήτηση στον πίνακα ή όχι. Η αναζήτηση ξεκινά για n=0 και επαναλαμβάνεται για n=1,2,3 κλπ εφόσον δεν βρεθεί η ζητούμενη λέξη. Η αναζήτηση επαναλαμβάνεται μόνο όταν εντοπίζονται θέσεις που έχουν περιεχόμενο διαφορετικό του επιθυμητού ή θέσεις έχουν διαγραφεί κατά το παρελθόν και περιέχουν τη δεσμευμένη λέξη “##tomb##”. Η αναζήτηση σταματά επιτυχώς εάν βρεθεί το επιθυμητό περιεχόμενο και ανεπιτυχώς εάν βρεθεί κενή θέση ή εάν επιστρέψουμε στην θέση του πίνακα από την οποία εκκινήσαμε την αναζήτηση για n=0.

### Διαγραφή από τον πίνακα κατακερματισμού
H διαγραφή προϋποθέτει ότι έχει γίνει επιτυχής αναζήτηση του στοιχείου προς διαγραφή. Κατά την διαγραφή είναι απαραίτητο να βάλουμε ένα χαρακτηριστικό που να δηλώνει ότι στη συγκεκριμένη θέση υπήρχε στοιχείο που διαγράφηκε. Κατά σύμβαση τοποθετούμε την λέξη “##tomb##”.
