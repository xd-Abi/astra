/** @format */

// pages/index.js
"use client";
import { useRouter } from "next/navigation";
import React, { useState } from "react";
import logo from "./logo_no_bg.png";
import Image from "next/image";

const Home = () => {
  const [searchInput, setSearchInput] = useState("");
  const router = useRouter();

  const handleSearch = (e: any) => {
    e.preventDefault();
    // Navigiere zur Suchergebnisseite mit dem eingegebenen Text als Query-Parameter
    router.push(`https://google.com/search?q=${searchInput}`);
  };

  return (
    <div className="min-h-screen flex flex-col justify-center items-center bg-gray-900">
      <main className="px-4 text-center">
        <div className="flex flex-col items-center">
          <Image src={logo} alt="logo" className="w-48 h-48" />
          <div className="mt-8">
            <form onSubmit={handleSearch} className="flex items-center">
              <input
                value={searchInput}
                onChange={(e) => setSearchInput(e.target.value)}
                type="text"
                placeholder="Search..."
                className="pr-10 pl-4 py-2 border rounded-md"
              />
              <button
                className="bg-blue-500 hover:bg-blue-700 text-white font-bold py-2 px-4 rounded-full ml-2"
                onClick={handleSearch}
              >
                Search
              </button>
            </form>
          </div>
        </div>
      </main>

      <footer className="mt-8 text-center text-white">
        <p>© 2024 Astra Web</p>
      </footer>
    </div>
  );
};

export default Home;
