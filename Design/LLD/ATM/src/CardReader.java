public class CardReader {

    public static boolean isValidCard(Card card)
    {
        System.out.println("Reading card");

        try{
            read(card);

            return true;
        }
        catch (InvalidCardException e)
        {
            System.out.println("invalid card");
            return false;
        }

    }

    public static void read(Card card) throws InvalidCardException
    {

    }
}
