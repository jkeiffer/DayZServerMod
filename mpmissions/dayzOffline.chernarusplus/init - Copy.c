void main()
{
	//INIT WEATHER BEFORE ECONOMY INIT------------------------
	Weather weather = g_Game.GetWeather();

	weather.MissionWeather(true);    // false = use weather controller from Weather.c

	//weather.GetOvercast().Set( Math.RandomFloatInclusive(0.4, 0.6), 1, 0);
	//weather.GetRain().Set( 0, 0, 1);
	//weather.GetFog().Set( Math.RandomFloatInclusive(0.05, 0.1), 1, 0);

	weather.GetOvercast().Set( Math.RandomFloatInclusive(0.4, 0.6), 1, 0);
	weather.GetRain().Set( 0, 0, 0);
	weather.GetFog().Set( Math.RandomFloatInclusive(0.05, 0.1), 1, 0);
	

//INIT ECONOMY--------------------------------------
	Hive ce = CreateHive();
	if ( ce )
		ce.InitOffline();

	//DATE RESET AFTER ECONOMY INIT-------------------------
	int year, month, day, hour, minute;
	int reset_month = 9, reset_day = 20;
	GetGame().GetWorld().GetDate(year, month, day, hour, minute);

	if ((month == reset_month) && (day < reset_day))
	{
		GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
	}
	else
	{
		if ((month == reset_month + 1) && (day > reset_day))
		{
			GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
		}
		else
		{
			if ((month < reset_month) || (month > reset_month + 1))
			{
				GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
			}
		}
	}
}

class CustomMission: MissionServer
{
	
	override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName)
	{
		Entity playerEnt;
		playerEnt = GetGame().CreatePlayer(identity, characterName, pos, 0, "NONE");//Creates random player
		Class.CastTo(m_player, playerEnt);

		GetGame().SelectPlayer(identity, m_player);

		return m_player;
	}

	override void StartingEquipSetup(PlayerBase player, bool clothesChosen)
	{
		player.RemoveAllItems();
			
		EntityAI itemEnt;
		ItemBase itemBs;
				
		player.GetInventory().CreateInInventory("HikingBootsLow_Grey"); 
		player.GetInventory().CreateInInventory("Shirt_WhiteCheck"); 
		player.GetInventory().CreateInInventory("Jeans_Blue");
 		//player.GetInventory().CreateInInventory("BaseballCap_CMMG_Black"); 
		//player.GetInventory().CreateInInventory("ThickFramesGlasses"); 
		player.GetInventory().CreateInInventory("Mag_1911_7Rnd");
		player.GetInventory().CreateInInventory("Mag_1911_7Rnd");
		player.GetInventory().CreateInInventory("AmmoBox_45ACP_25rnd");
		player.GetInventory().CreateInInventory("Matchbox");
		player.GetInventory().CreateInInventory("Canteen");
		//player.GetInventory().CreateInInventory("HuntingKnife");
		player.GetInventory().CreateInInventory("KitchenKnife");
		player.GetInventory().CreateInInventory("Rice");
		player.GetInventory().CreateInInventory("BandageDressing");
		//player.GetInventory().CreateInInventory("WorkingGloves_Yellow"); 
		player.GetInventory().CreateInInventory("Hatchet");
		//player.GetInventory().CreateInInventory("WeaponCleaningKit");
		
		EntityAI gun = player.GetHumanInventory().CreateInHands("Colt1911");
		itemEnt = player.GetInventory().CreateInInventory("Rag");
		itemBs = ItemBase.Cast(itemEnt);
		itemBs.SetQuantity(4);

		EntityAI car;
		vector NewPosition;
		vector OldPosition;
		OldPosition = player.GetPosition();
		NewPosition[0] = OldPosition[0] + 2;
		NewPosition[1] = OldPosition[1] + 0.2;
		NewPosition[2] = OldPosition[2] + 2;
	
		car.SetAllowDamage(false);
		
		car = GetGame().CreateObject( "OffroadHatchback", NewPosition, false, true, true );
		car.GetInventory().CreateAttachment("HatchbackHood");
		car.GetInventory().CreateAttachment("HatchbackTrunk");
		car.GetInventory().CreateAttachment("HatchbackDoors_Driver");
		car.GetInventory().CreateAttachment("HatchbackDoors_CoDriver");
		car.GetInventory().CreateAttachment("HatchbackWheel");
		car.GetInventory().CreateAttachment("HatchbackWheel");
		car.GetInventory().CreateAttachment("HatchbackWheel");
		car.GetInventory().CreateAttachment("HatchbackWheel");
		car.GetInventory().CreateAttachment("HatchbackWheel"); //spare
		car.GetInventory().CreateAttachment("SparkPlug");
		car.GetInventory().CreateAttachment("EngineBelt");
		car.GetInventory().CreateAttachment("CarBattery");
		car.GetInventory().CreateAttachment("CarRadiator");
		car.GetInventory().CreateInInventory("LugWrench");
		car.GetInventory().CreateInInventory("FirstAidKit");
		car.GetInventory().CreateInInventory("CanisterGasoline");
		car.GetInventory().CreateInInventory("Canteen");
		
		auto carfluids = Car.Cast( car );
		carfluids.Fill( CarFluid.FUEL, 1000 );
		carfluids.Fill( CarFluid.OIL, 1000 );
		carfluids.Fill( CarFluid.BRAKE, 1000 );
		carfluids.Fill( CarFluid.COOLANT, 1000 );

	
	}
	
};

Mission CreateCustomMission(string path)
{
	return new CustomMission();
}
