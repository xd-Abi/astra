'use client';
import React, { useState } from 'react';
import { useRouter } from 'next/navigation';
import Image from 'next/image';
import Background from '@public/images/background.png';
import DiscordIcon from '@public/images/discord-icon.png';
import WhatsAppIcon from '@public/images/whats-app-icon.png';
import TwitchIcon from '@public/images/twitch-icon.png';

export default function Home() {
  const [searchInput, setSearchInput] = useState('');
  const router = useRouter();

  function handleSearch(e: React.FormEvent) {
    e.preventDefault();
    router.push(`https://www.google.com/search?q=${searchInput}`);
  }

  return (
    <main className="w-full min-h-screen bg-black overflow-x-hidden flex justify-center items-center">
      <Image
        src={Background}
        width={2129}
        height={1377}
        alt="Background"
        className="z-0 fixed bg-cover bg-center w-full"
      />
      <div className="z-50 w-[50vw] h-[40vh] bg-black bg-opacity-50 backdrop-blur-2xl rounded-3xl px-3 py-6">
        <p className="text-2xl text-white font-medium">👋 Good Afternoon</p>
        <form
          className="w-full bg-black bg-opacity-20 px-3 py-3 mt-5 rounded-lg flex items-center text-stone-400 gap-2"
          onSubmit={handleSearch}
        >
          <svg
            xmlns="http://www.w3.org/2000/svg"
            fill="none"
            viewBox="0 0 24 24"
            strokeWidth={1.5}
            stroke="currentColor"
            className="w-6 h-6"
          >
            <path
              strokeLinecap="round"
              strokeLinejoin="round"
              d="m21 21-5.197-5.197m0 0A7.5 7.5 0 1 0 5.196 5.196a7.5 7.5 0 0 0 10.607 10.607Z"
            />
          </svg>
          <input
            type="text"
            placeholder="Type something to search for"
            className="w-full h-full font-light text-lg placeholder:text-stone-400 text-white outline-none border-none bg-transparent"
            onChange={(e) => setSearchInput(e.target.value)}
          ></input>
        </form>
        <p className="mt-10 text-lg text-white font-medium">Most used apps</p>
        <div className="flex gap-8 items-center mt-3">
          <Image
            width={50}
            height={50}
            src={DiscordIcon}
            alt="Discord"
            className="hover:scale-105 transition-all duration-200 ease-in cursor-pointer"
          />
          <Image
            width={50}
            height={50}
            src={WhatsAppIcon}
            alt="WhatsApp"
            className="hover:scale-105 transition-all duration-200 ease-in cursor-pointer"
          />
          <Image
            width={50}
            height={50}
            src={TwitchIcon}
            alt="Twitch"
            className="hover:scale-105 transition-all duration-200 ease-in cursor-pointer"
          />
        </div>
      </div>
    </main>
  );
}
