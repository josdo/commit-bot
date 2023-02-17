/* Allows services on either PIC to post an event to each other as if on the same PIC.
   Handles all the SPI communication to convey the event to the right service. */

// Leader

Init()
{
  // Setup SPI for leader mode
}

/* All FollowerPIC32 services. */
PostToDCMotorService(e)
{
  PostToFollower(e);
}

PostToFollowerEventOverSPI();

ES_EventType_t followerEvents[] = {ES_TEST_TO_FOLLOWER};

Run()
{
  // if ES_FOLLOWER_SPI_EVENT
    // DecodePost to all
  // else
    // EncodeSend to follower PIC
}

/* When event over SPI received, interrupt and post ES_FOLLOWER_SPI_EVENT to the FollowerEvent service. */
ISR_FollowerEventOverSPI();
{
  // Got an event to a follower
  // Got an event from a follower
}

EncodeSend();
    // Encode into 16 bits
    // Send over SPI

DecodePost();
    // Decode from 16 bits
    // Post to correct service
